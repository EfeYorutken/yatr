#include <array>
#include <ftxui/screen/terminal.hpp>
#include <set>//i am getting some error when i try to use unordered, dont know why, will fix later

#include "utils.cpp"

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/app.hpp>


enum class MOVEMENT{
	RIGHT,
	LEFT,
	DOWN
};

template<std::size_t dim_w, std::size_t dim_h>
class Engine{

	private:

		std::array<bool, dim_w * dim_h> board;
		std::set<Vector2D> filled_cells;
		ftxui::Screen screen;

	public:

		Engine() :
			screen(
					ftxui::Screen::Create(ftxui::Dimension::Fixed(dim_w),
						ftxui::Dimension::Fixed(dim_w))
					){

				this->board.fill(dim_w * dim_h);
				this->filled_cells = {};
			}

		void start(){

		}

		void move_piece(MOVEMENT m){}
		void display(){
			this->screen.Print();
		}

};
