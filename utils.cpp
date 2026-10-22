#pragma once

#include <utility>

typedef std::pair<int, int> Vector2D;//an actual vector, not a dynamic array

typedef std::pair<Vector2D, Vector2D> Matrix2D;//{ i, j }
/*
	 {

	 	{ ix, iy },
		{ jx, jy }

	 }
 */

Vector2D apply_transformation(Vector2D v, Matrix2D transformation){

	Vector2D i = transformation.first;
	Vector2D j = transformation.second;

	int ix = i.first;
	int iy = i.second;

	int jx = j.first;
	int jy = j.second;

	int x = v.first;
	int y = v.second;

	int fin_x = x * ( jx + ix );
	int fin_y = y * ( jy + iy );

	return { fin_x, fin_y };
}

const Matrix2D CLOCK_WISE_ROTATION = {
	{ 0,-1 },
	{ 1,0 }
};

const Matrix2D COUNTER_CLOCK_WISE_ROTATION = {
	{ 0,1 },
	{ -1, 0 }
};

/*
 these are sheeer operations (i think)
 do not cheat of off main, implement the sheer and see how that goes
 */
const Matrix2D MOVE_RIGHT = {
	{ 2,0 },
	{ 0,1 }
};

const Matrix2D MOVE_LEFT = {
	{ 2,0 },
	{ 0,1 }
};
