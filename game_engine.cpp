#include <array>
#include <format>
#include <optional>
#include <print>

#include "utils.cpp"
#include "tetris_piece.cpp"

#include <ftxui/dom/canvas.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/app.hpp>
#include <ftxui/component/event.hpp>

enum class MOVEMENT{
	RIGHT,
	LEFT,
	DOWN,
	NONE
};

template<std::size_t dim_w, std::size_t dim_h, std::size_t col_count>
class Engine{

	private:

		std::array<bool, dim_w * dim_h> board;
		std::array<unsigned int, dim_h> occupancy_per_row;//this is a bad idea for displace, cant show holes
		ftxui::Canvas drawable_board;
		std::size_t cell_size;

		Piece current;
		std::optional<Piece> held;
		Piece next;

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

		void constexpr swap_held(){
			if( !this->held ){
				this->held = this->current;
				this->current = get_random_piece();
			}
			Piece temp = this->current;
			this->current = this->held.value();
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

	public:

		Engine() {

				this->board.fill(false);
				this->cell_size = dim_w / col_count;
				this->occupancy_per_row.fill(0);

				this->drawable_board = ftxui::Canvas(int(dim_w / 2), dim_h);

				this->current = get_random_piece();
				this->next = get_random_piece();

				this->x_displace = dim_w / 2;
				this->y_displace = dim_h / 2;

			}

		void start(){

			ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::FixedSize(dim_w, dim_h);

			auto drawer = [&](ftxui::Canvas& c){

				for(Vector2D block : this->current.pieces){
					c.DrawBlock(block.first * cell_size, block.second * cell_size, true, ftxui::Color::Red);
				}

			};

			ftxui::Component drw_brd_component = ftxui::Renderer([&]() {

					auto board = ftxui::canvas(dim_w * 2, dim_h * 4, drawer)
					| ftxui::size(ftxui::WIDTH, ftxui::EQUAL, dim_w)
					| ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, dim_h)
					| ftxui::border;

					return ftxui::hbox({
							board,
							ftxui::filler(),
							});
					});

			ftxui::Components all_components = {
				drw_brd_component
			};

			screen.Loop( ftxui::Container::Horizontal(all_components) );
		}

		void move_piece(MOVEMENT m){}
};
