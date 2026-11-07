#include "utils.cpp"

#include <vector>
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

		void rotate_ccw(){
			this->rotate_with(COUNTER_CLOCK_WISE_ROTATION );
		}

		void rotate_cw(){
			this->rotate_with(CLOCK_WISE_ROTATION);
		}

};

const std::array<Piece, 7> TETRIS_PIECES = {

	Piece({//I piece
			{0,0},
			{0,1},
			{0,2},
			{0,3},
			}),

	Piece({//O piece
			{0,0},
			{1,0},
			{0,1},
			{1,1},
			}),

	Piece({//T piece
			{0,0},
			{1,0},
			{2,0},
			{1,1}
			}),

	Piece({//S piece
			{0,0},
			{1,0},
			{1,1},
			{2,1}
			}),

	Piece({//Z piece
			{0,1},
			{1,1},
			{1,0},
			{2,0}
			}),

	Piece({//J piece
			{0,0},
			{1,0},
			{1,1},
			{1,2},
			}),

	Piece({//L piece
			{0,0},
			{1,0},
			{0,1},
			{0,2},
			}),
};
