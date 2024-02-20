#include "Shapes.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <math.h>

void Shapes::init_shape() {

	curr_pos = 0;
	num_of_positions = 0;
	int bomb = rand() % GameConfig::BOMB_PROBABILITY;
	if (bomb == 0) {
		initBomb();
	}
	else
	{
		int type = rand() % GameConfig::SHAPE_PROBABILITY + 1;

		switch (type)
		{
		case (int)shapeType::SQUARE:
			init_square();
			break;
		case (int)shapeType::N:
			init_N();
			break;
		case (int)shapeType::N_MIRROR:
			init_N_mirror();
			break;
		case (int)shapeType::L:
			init_L();
			break;
		case (int)shapeType::L_MIRROR:
			init_L_mirror();
			break;
		case (int)shapeType::PLUS:
			init_plus();
			break;
		case (int)shapeType::I:
			init_I();
			break;

		}
	}
}


void Shapes::initBomb() {
	num_of_positions = 1;
	vec_shape_positions.resize(1);
	vec_shape_positions[0].init(Point(5, 0));

}

void  Shapes::init_square() {
	num_of_positions = 1;
	vec_shape_positions.resize(1);
	vec_shape_positions[0].init(Point(5, 0), Point(5, 1), Point(6, 0), Point(6, 1));

}

void Shapes::init_N() {
	num_of_positions = 2;
	vec_shape_positions.resize(2);
	vec_shape_positions[0].init(Point(5, 2), Point(6, 1), Point(5, 1), Point(6, 0));
	vec_shape_positions[1].init(Point(6, 1), Point(6, 0), Point(5, 0), Point(7, 1));

}

void Shapes::init_N_mirror() {
	num_of_positions = 2;
	vec_shape_positions.resize(2);
	vec_shape_positions[0].init(Point(6, 2), Point(5, 1), Point(6, 1), Point(5, 0));
	vec_shape_positions[1].init(Point(5, 1), Point(6, 1), Point(6, 0), Point(7, 0));

}

void Shapes::init_L() {
	num_of_positions = 4;
	vec_shape_positions.resize(4);
	vec_shape_positions[0].init(Point(5, 2), Point(5, 1), Point(5, 0), Point(6, 2));
	vec_shape_positions[1].init(Point(5, 1), Point(5, 0), Point(6, 0), Point(7, 0));
	vec_shape_positions[2].init(Point(6, 2), Point(6, 0), Point(6, 1), Point(5, 0));
	vec_shape_positions[3].init(Point(5, 1), Point(6, 1), Point(7, 1), Point(7, 0));

}

void Shapes::init_L_mirror() {
	num_of_positions = 4;
	vec_shape_positions.resize(4);
	vec_shape_positions[0].init(Point(5, 2), Point(6, 2), Point(6, 1), Point(6, 0));
	vec_shape_positions[1].init(Point(5, 1), Point(5, 0), Point(6, 1), Point(7, 1));
	vec_shape_positions[2].init(Point(5, 2), Point(5, 1), Point(5, 0), Point(6, 0));
	vec_shape_positions[3].init(Point(7, 1), Point(6, 0), Point(7, 0), Point(5, 0));
}

void Shapes::init_plus() {
	num_of_positions = 4;
	vec_shape_positions.resize(4);
	vec_shape_positions[0].init(Point(5, 1), Point(6, 1), Point(7, 1), Point(6, 0));
	vec_shape_positions[1].init(Point(5, 2), Point(5, 1), Point(5, 0), Point(6, 1));
	vec_shape_positions[2].init(Point(6, 1), Point(6, 0), Point(7, 0), Point(5, 0));
	vec_shape_positions[3].init(Point(6, 2), Point(6, 1), Point(6, 0), Point(5, 1));
}

void Shapes::init_I() {
	num_of_positions = 2;
	vec_shape_positions.resize(2);
	vec_shape_positions[0].init(Point(5, 3), Point(5, 1), Point(5, 2), Point(5, 0));
	vec_shape_positions[1].init(Point(5, 0), Point(6, 0), Point(7, 0), Point(8, 0));
}

void Shapes::printCurrPos(char ch, int min_x) const {
	vec_shape_positions[curr_pos].printShape(ch, min_x);
}

void Shapes::moveShape(GameConfig::eKeys key, int min_x) {
	for (int i = 0; i < num_of_positions; i++) {
		vec_shape_positions[i].moveCoords(key, min_x);
	}
}

void Shapes::rotate(GameConfig::eKeys key, int min_x) {
	if (min_x == GameConfig::MIN_X_LEFT)
	{
		switch (key)
		{
		case GameConfig::eKeys::ROTATE_CLOCKWISE_L_LEFTP:
		case GameConfig::eKeys::ROTATE_CLOCKWISE_U_LEFTP:
		{
			curr_pos++;
			if (curr_pos > num_of_positions - 1) {
				curr_pos = 0;
			}
			break;
		}
		case GameConfig::eKeys::ROTATE_COUNTER_CLOCKWISE_L_LEFTP:
		case GameConfig::eKeys::ROTATE_COUNTER_CLOCKWISE_U_LEFTP:
		{
			curr_pos--;
			if (curr_pos < 0) {
				curr_pos = num_of_positions - 1;
			}
			break;
		}

		}
	}

	else
	{
		switch (key)
		{
		case GameConfig::eKeys::ROTATE_CLOCKWISE_L_RIGHTP:
		case GameConfig::eKeys::ROTATE_CLOCKWISE_U_RIGHTP:
		{
			curr_pos++;
			if (curr_pos > num_of_positions - 1) {
				curr_pos = 0;
			}
			break;
		}
		case GameConfig::eKeys::ROTATE_COUNTER_CLOCKWISE_L_RIGHTP:
		case GameConfig::eKeys::ROTATE_COUNTER_CLOCKWISE_U_RIGHTP:
		{
			curr_pos--;
			if (curr_pos < 0) {
				curr_pos = num_of_positions - 1;
			}
			break;
		}

		}
	}


}

Shape Shapes::getShape() const {
	return vec_shape_positions[curr_pos];
}

void Shapes::initRandomShape(std::vector<Point>& arr_coords) {
	num_of_positions = 1;
	curr_pos = 0;
	vec_shape_positions.resize(1);
	vec_shape_positions[0].init(arr_coords);
}

int Shapes::getNumOfPositions() const {
	return num_of_positions;
};

Shape Shapes::getShape(int wanted_pos) const {
	return vec_shape_positions[wanted_pos];
};

void Shapes::setCurrPos(int wanted_pos) {
	curr_pos = wanted_pos;
};

