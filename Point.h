#pragma once

#include "gameConfig.h"

class Point
{
	int x;
	int y;
	int diff_x = 0;
	int diff_y = 1;

public:
	void init(int x, int y);
	void draw(char ch, int min_x) const;
	void move(GameConfig::eKeys key, int min_x);
	int get_x() const;
	int get_y() const;

	Point() {
		x = 0;
		y = 0;
	};
	Point(int _x, int _y) :x(_x), y(_y) {};
	void addX(int x) {
		this->x = this->x + x;
	}
};