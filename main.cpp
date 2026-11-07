#include <vector>
#include <print>
#include <utility>

#include "utils.cpp"
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

	std::array<bool, w*h> board;

	for(auto p : TETRIS_PIECES){

		board.fill(false);

		for(auto cords : p.pieces){
			int x = cords.first;
			int y = cords.second;

			board.at(x + y * w) = true;

		}

		print_board(board);

		std::print("\n----\n");

	}

	return 0;
}
