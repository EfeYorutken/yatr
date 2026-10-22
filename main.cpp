#include <print>
#include <utility>

#include "utils.cpp"

int main(){

	Vector2D p = { 1,1 };

	Matrix2D move_right = {
		{ 2, 0 },
		{ 0,1 }
	};

	Vector2D p2 = apply_transformation( p, move_right );

	print("{}\n", p2);

	return 0;
}
