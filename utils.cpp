#pragma once

#include <print>

#include <utility>

typedef std::pair<int, int> Vector2D;//an actual vector, not a dynamic array

typedef std::pair<Vector2D, Vector2D> Matrix2D;//{ i, j }
/*
	 {

	 	{ ix, iy },
		{ jx, jy }

	 }
 */

Vector2D constexpr apply_movement(Vector2D v, Matrix2D movement){

	Vector2D i = movement.first;
	Vector2D j = movement.second;

	int ix = i.first;
	int iy = i.second;

	int jx = j.first;
	int jy = j.second;

	int x = v.first;
	int y = v.second;

	int fin_x = x + ix + jx;
	int fin_y = y + iy + jy;

	return { fin_x, fin_y };

}

std::pair<int,int> operator*(std::pair<int,int> v, int x){

	return { v.first * x, v.second * x };

}

std::pair<int,int> operator+(std::pair<int, int> v1, std::pair<int, int> v2){

	return{ v1.first + v2.first, v1.second + v2.second };
}

Vector2D constexpr apply_transformation(Vector2D v, Matrix2D transformation){
	std::pair<int, int> i = transformation.first;
	std::pair<int, int> j = transformation.second;

	int x = v.first;
	int y = v.second;

	std::pair<int,int> x2 = i * x;
	std::pair<int,int> y2 = j * y;

	return x2 + y2;
}

const Matrix2D CLOCK_WISE_ROTATION = {
	{ 0,-1 },
	{ 1,0 }
};

const Matrix2D COUNTER_CLOCK_WISE_ROTATION = {
	{ 0,1 },
	{ -1, 0 }
};
