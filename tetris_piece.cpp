#include "utils.cpp"

#include <vector>
#include <cstdlib>
#include <ctime>
#include <array>
#include <algorithm>

class Piece{

	private:
		void rotate_with(Matrix2D mat){
			decltype(this->pieces) rotated_pieces = this->pieces;

			std::transform(this->pieces.begin(), this->pieces.end(), rotated_pieces.begin(),
					[&mat](Vector2D p){
					return apply_transformation( p, mat  );
					});

			this->pieces = rotated_pieces;
		}

	public:
		std::vector<Vector2D> pieces;

		Piece( std::vector<Vector2D> ps ) : pieces(ps){}

		template<size_t W, size_t H>
			Piece( std::array<std::array<bool, W>,H> drawing){
				this->pieces = {};

				for(int i = 0; i < H; ++i){
					for(int j = 0; j < W; ++j){

						int x = W - j - 1;
						int y = H - i - 1;

						if( drawing.at(i).at(j) ){ this->pieces.push_back({x,y}); }
					}
				}

			}

		void rotate_ccw(){ this->rotate_with(COUNTER_CLOCK_WISE_ROTATION ); }
		void rotate_cw(){ this->rotate_with(CLOCK_WISE_ROTATION); }

};

const std::array<Piece, 7> TETRIS_PIECES = {

	Piece({ {0,0}, {0,1}, {0,2}, {0,3}, }), //I piece

	Piece({ {0,0}, {1,0}, {0,1}, {1,1}, }), //O piece

	Piece({ {0,0}, {1,0}, {2,0}, {1,1} }), //T piece

	Piece({ {0,0}, {1,0}, {1,1}, {2,1} }), //S piece

	Piece({ {0,1}, {1,1}, {1,0}, {2,0} }), //Z piece

	Piece({ {0,0}, {1,0}, {1,1}, {1,2}, }), //J piece

	Piece({ {0,0}, {1,0}, {0,1}, {0,2}, }), //L piece
};

Piece constexpr get_random_piece(){
	srand(time(0));

	return TETRIS_PIECES.at(rand() % TETRIS_PIECES.size()); 
}
