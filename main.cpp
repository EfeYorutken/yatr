#include <array>
#include <print>

#include "tetris_piece.cpp"

const int w = 20;
const int h = 5;

void print_board(std::array<bool, w * h> b){

	for(int i = h-1; i >= 0; --i){

		for(int j = 0; j < w; ++j){
			bool piece_of_piece = b.at( i*w + j);
			std::print("{} ", piece_of_piece ? '#' : '.'  );
		}

		std::print("\n");

	}

}

int main(){

	std::array<std::array<bool, 3>, 3> drawing = {{

		{false, false, false},
		{false, true, false},
		{true, true, true},

	}};

	std::array<bool, w * h> board;
	board.fill(false);

	Piece random_piece = get_random_piece();

	for(auto p : random_piece.pieces){
		board.at(p.first + p.second * w) = true;
	}

	print_board(board);

	return 0;
}
