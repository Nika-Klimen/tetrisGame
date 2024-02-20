#pragma once
#include <vector>
#include "Point.h"

class Shape
{
private:
	std::vector<Point> arr_coords;

public:
	void init(Point&& p1, Point&& p2, Point&& p3, Point&& p4);
	void init(Point&& p1);
	void init(std::vector<Point>& arr_coords);
	void printShape(char ch, int min_x) const;
	void moveCoords(GameConfig::eKeys key, int min_x);
	bool isMoveValid(GameConfig::eKeys key, int min_x) const;
	std::vector<Point> getCoordsArr() const;
	Shape() { arr_coords.reserve(4); }
	friend Shape getLowerShape(Shape& s1, Shape& s2);
	friend bool isSameShape(Shape& s1, Shape& s2);
	int getNumOfXInLowestY();
};