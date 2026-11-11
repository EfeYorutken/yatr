/*
	 implement the engine.cpp
 */

#include <array>
#include <print>

#include "game_engine.cpp"

const int w = 20;
const int h = 35;

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

	Engine<w, h, 10> engine;

	engine.display();

	return 0;
}
