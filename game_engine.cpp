#include <algorithm>
#include <array>
#include <chrono>
#include <climits>
#include <thread>
#include <format>

#include "utils.cpp"
#include "tetris_piece.cpp"

#include <ftxui/dom/canvas.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/app.hpp>
#include <ftxui/component/event.hpp>

template<std::size_t dim_w, std::size_t dim_h, std::size_t col_count>
class Engine{

	private:

		std::array<bool, dim_w * dim_h> board;
		std::array<unsigned int, dim_h> occupancy_per_row;//this is a bad idea for displace, cant show holes
		ftxui::Canvas drawable_board;
		std::size_t cell_size;

		Piece current;
		Piece held;
		Piece next;

		Vector2D movement2apply;
		Matrix2D rotation2apply;

		int x_displace;
		int y_displace;

		Piece get_displaced_piece(){
			Piece res = this->current;

			Vector2D displacement = { this->x_displace, this->y_displace };

			for(Vector2D& block : res.pieces){
				block = block + displacement;
			}

			return res;
		}

		Vector2D get_delta_from_origin(const Piece& p){
			Vector2D delta_top_left = {INT_MAX, INT_MAX};

			//get the delta
			for(Vector2D block : this->current.pieces){
				delta_top_left = { std::min( block.first, delta_top_left.first ),
					std::min( block.second, delta_top_left.second )
				};
			}

			return delta_top_left;
		}

		void constexpr swap_held(){

			if( this->held.pieces.empty() ){
				this->held = this->current;
				this->current = get_random_piece();
			}
			Piece temp = this->current;
			this->current = this->held;
			this->held = temp;
		}

		void constexpr swap_next(){//next is always defined
			Piece temp = this->current;
			this->current = this->next;
			this->next = get_random_piece();
		}

		void current_to_board(){
			for(Vector2D point : this->current.pieces){

				int x = point.first;
				int y = point.second;

				this->board.at(y * dim_w + x) = true;

			}
		}

		ftxui::Component get_component_for_piece(const Piece& p, std::pair<int, int> d){

			return ftxui::Renderer([&p, this, d](){

					auto drawer = [&](ftxui::Canvas& c){
					for(Vector2D block : p.pieces){
					//craetes pieces that are seperated too much. will fix later
					c.DrawBlock(block.first * cell_size, block.second * cell_size, true, ftxui::Color::Red);
					}
					};

					auto res = ftxui::canvas(  d.first, d.second, drawer )
					| ftxui::size(ftxui::WIDTH, ftxui::EQUAL, d.first)
					| ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, d.second)
					| ftxui::border;

					return ftxui::vbox(ftxui::hbox(res));

					});

		}

	public:

		Engine() {

			this->board.fill(false);
			this->cell_size = dim_w / col_count;
			this->occupancy_per_row.fill(0);
			this->held = Piece();

			this->drawable_board = ftxui::Canvas(int(dim_w / 2), dim_h);

			this->next = get_random_piece();
			this->current = get_random_piece();

			/*
				 for(auto& block : this->current.pieces){
				 block = Vector2D{ dim_w / 2, dim_h / 2 } + block;
				 }
				 */

			this->x_displace = dim_w / 2;
			this->y_displace = dim_h / 2;

			this->movement2apply = { 0, 1 };//assuming down is +1
			this->rotation2apply = NO_ROTATION;

		}

		void start(){

			ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::FixedSize(dim_w, dim_h);
			std::atomic<bool> running = true;

			ftxui::Component test_component = ftxui::Renderer([this](){

					ftxui::Elements children = {};

					for(auto p : this->current.pieces){
					children.push_back( ftxui::text(std::format("({}, {})", p.first, p.second)) 
							| ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 50)
							| ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 50)
							| ftxui::border
							| ftxui::border );
					}

					return ftxui::vbox(children);
					});

			ftxui::Component held_piece = 
				this->get_component_for_piece(this->held, {dim_w/5, dim_h/5});

			std::thread ticker( [&running, &screen](){

					while(running){
					//make this into miliseconds or whatever and speed it up when a line is cleaned
					std::this_thread::sleep_for(std::chrono::seconds(1));
					screen.PostEvent(ftxui::Event::Custom);
					}

					} );

			ftxui::Component drw_brd_component = 
				this->get_component_for_piece(this->current, {dim_w * 2, dim_h * 4});

			ftxui::Components all_components = {
				held_piece,
				drw_brd_component,
			};

			ftxui::Component root = ftxui::Container::Horizontal(all_components) |
				ftxui::CatchEvent([this](ftxui::Event e){
						if(e == ftxui::Event::Custom){
						/*
							 move the piece to the top left
							 rotate
							 move back inside the board if needs be
							 move back to the original place
							 apply movement2apply
							 reset movements
							 adjust the piece to be in the board
							 */

						//get the delta
						Vector2D delta_top_left = this->get_delta_from_origin(this->current);

						//apply delta to move the piece to the top left
						//apply transformation
						//move back to the original location
						//apply the movement
						for(Vector2D& block : this->current.pieces){
							block = block - delta_top_left;
							block = block * this->rotation2apply;
							block = block + delta_top_left + movement2apply;
						}

						this->rotation2apply = NO_ROTATION;
						this->movement2apply = { 0,1 };

						int left_most_block_x = INT_MAX;
						int right_most_block_x = INT_MIN;

						//TODO
						//might want to 'cache' the down most/upmost/leftmost/rightmost pieces
						//values of which will change after rotation and movement
						//rather than looping over all the blocks ever frame, can simply
						//look at the values
						//
						for(Vector2D block : this->current.pieces){
							right_most_block_x = std::max(block.first, right_most_block_x);
							left_most_block_x = std::min(block.first, left_most_block_x);
						}

						if(left_most_block_x < 0){
							const Vector2D temp = { -left_most_block_x, 0 };
							for(Vector2D& block : this->current.pieces){
								block = block + temp;
							}
						}

						if(right_most_block_x > this->drawable_board.width()){
							const Vector2D temp = { -right_most_block_x, 0 };
							for(Vector2D& block : this->current.pieces){
								block = block + temp;
							}
						}

						return true;
						}
						else{

							//TODO
							//there are methods for rotating the piece, might be clenear to use those
							if( e == ftxui::Event::ArrowLeft  ){
								this->movement2apply = this->movement2apply + 
									( this->movement2apply == Vector2D{0,1} ?
										Vector2D{-1,0} :
										Vector2D{0,0} );
							}
							else if( e == ftxui::Event::ArrowRight ){
								this->movement2apply = this->movement2apply + 
									( this->movement2apply == Vector2D{0,1} ?
										Vector2D{1,0} :
										Vector2D{0,0} );
							}
							else if( e == ftxui::Event::ArrowDown){

								this->rotation2apply = this->rotation2apply == NO_ROTATION ?
									COUNTER_CLOCK_WISE_ROTATION :
									this->rotation2apply;

							}
							else if( e == ftxui::Event::ArrowUp    ){
								this->rotation2apply = this->rotation2apply == NO_ROTATION ?
									CLOCK_WISE_ROTATION  :
									this->rotation2apply;

							}

						}

						return false;
				});

			screen.Loop( root );

			running = false;
			if(ticker.joinable()){ ticker.join(); }

		}

};
