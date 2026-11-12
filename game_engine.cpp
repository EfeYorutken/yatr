#include <array>
#include <optional>

#include "utils.cpp"
#include "tetris_piece.cpp"

#include <ftxui/dom/canvas.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
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
		std::array<unsigned int, dim_h> occupancy_per_row;
		ftxui::Screen screen = ftxui::Screen::Create(ftxui::Dimension::Fixed(dim_w), ftxui::Dimension::Fixed(dim_w));;
		ftxui::Canvas drawable_board;
		std::size_t cell_size;
		Piece current;
		std::optional<Piece> held;
		Piece next;

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

				this->drawable_board = ftxui::Canvas(dim_w, dim_h);

				this->current = get_random_piece();
				this->next = get_random_piece();

			}

		void start(){

		}

		void move_piece(MOVEMENT m){}
		void display(){

			this->current_to_board();

			for(int i = 0; i < dim_h; ++i){
				for(int j = 0; j < dim_w; ++j){

					if( this->board.at(i * dim_w + j) ){
						this->drawable_board.DrawBlock(j * cell_size, i * cell_size,
								true, ftxui::Color::Red);
					}

				}
			}

			auto bordered_board = ftxui::canvas(&(this->drawable_board))
				| ftxui::border 
				| ftxui::color(ftxui::Color::Cyan);
			ftxui::Render(this->screen, bordered_board);

			this->screen.Print();

		}

};
