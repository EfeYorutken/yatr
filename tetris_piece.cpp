#include "utils.cpp"

#include <array>
#include <algorithm>

template<std::size_t S>
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
		std::array<Vector2D,S> pieces;

		void rotate_ccw(){
			this->rotate_with(COUNTER_CLOCK_WISE_ROTATION );
		}

		void rotate_cw(){
			this->rotate_with(CLOCK_WISE_ROTATION);
		}

		void move_right(){}
		void move_left(){}
		void move_down(){}
		void project(){}

};
