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
		ftxui::Canvas drawable_board;
		std::size_t cell_size;

		Piece current;
		Piece held;
		Piece next;

		int current_piece_lowest;
		int current_piece_right_most;
		int current_piece_left_most;

		Piece get_displaced_piece(){
			Piece res = this->current;

			return res;
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

		void move_current_to_right(int board_right_limit){

			if((this->current_piece_right_most * cell_size) < board_right_limit ){
				this->current.move_right1();
				++this->current_piece_left_most;
				++this->current_piece_right_most;
			}
		}

		void move_current_to_left(){

			if(this->current_piece_left_most != 0){
				this->current.move_left1();
				--this->current_piece_left_most;
				--this->current_piece_right_most;
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

					auto res = ftxui::canvas(  d.first * 2, d.second * 4, drawer )
					| ftxui::size(ftxui::WIDTH, ftxui::EQUAL, d.first)
					| ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, d.second)
					| ftxui::border;

					return ftxui::vbox(ftxui::hbox(res));

					});

		}

		void set_mosts(){//for setting the left most, right most etc coordinates

			this->current_piece_left_most = INT_MAX;
			this->current_piece_right_most = INT_MIN;
			this->current_piece_lowest = INT_MIN;

			for(Vector2D block : this->current.pieces){

				this->current_piece_left_most = std::min( block.first,this->current_piece_left_most );
				this->current_piece_right_most = std::max( block.first,this->current_piece_right_most );
				this->current_piece_lowest = std::max( block.second, this->current_piece_lowest );

			}

		}

	public:

		Engine() {

			this->board.fill(false);
			this->cell_size = dim_w / col_count;
			this->held = Piece();

			this->drawable_board = ftxui::Canvas(int(dim_w/2), dim_h);

			this->next = get_random_piece();
			this->current = get_random_piece();

			this->set_mosts();

		}

		void start(){
		}

};
