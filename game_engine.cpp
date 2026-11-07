#include <array>
#include <set>//because hashing

#include "utils.cpp";

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


	public:
		void display(){}
		void move_piece(MOVEMENT m){}

};
