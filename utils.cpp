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


Vector2D constexpr operator*(Vector2D v, int x){

	return { v.first * x, v.second * x };

}

Vector2D constexpr operator+(std::pair<int, int> v1, std::pair<int, int> v2){
	return{ v1.first + v2.first, v1.second + v2.second };
}

Vector2D constexpr operator*(Vector2D v, Matrix2D transformation){
	Vector2D newi = transformation.first;
	Vector2D newj = transformation.second;

	int ic = v.first;
	int jc = v.second;

	return ( newi * ic ) + ( newj * jc );
}

Vector2D constexpr operator-(std::pair<int, int> v1, std::pair<int, int> v2){
	return{ v1.first - v2.first, v1.second - v2.second };
}

const Matrix2D CLOCK_WISE_ROTATION = {
	{ 0,-1 },
	{ 1,0 }
};

const Matrix2D COUNTER_CLOCK_WISE_ROTATION = {
	{ 0,1 },
	{ -1, 0 }
};

const Matrix2D NO_ROTATION = {
	{ 1,0 },
	{ 0,1 }
};
