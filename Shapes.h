#pragma once

#include <stdlib.h>
#include <time.h>
#include <vector>

#include "Shape.h"
#include "Point.h"



class Shapes
{
private:
	std::vector<Shape> vec_shape_positions;
	int curr_pos;
	int num_of_positions;
	enum class shapeType { SQUARE = 1, N, N_MIRROR, L, L_MIRROR, PLUS, I };

public:
	void init_shape();
	void init_square();
	void init_N();
	void init_N_mirror();
	void init_L();
	void init_L_mirror();
	void init_plus();
	void init_I();
	void initBomb();
	void printCurrPos(char ch, int min_x) const;
	void moveShape(GameConfig::eKeys key, int min_x);
	void rotate(GameConfig::eKeys key, int min_x);
	Shape getShape() const;
	int getNumOfPositions() const;
	void initRandomShape(std::vector<Point>& arr_coords);
	Shapes() { vec_shape_positions.reserve(4); }
	Shape getShape(int wanted_pos) const;
	void setCurrPos(int wanted_pos);
	void UpdateCurrPos() {
		curr_pos++;
	};

};
