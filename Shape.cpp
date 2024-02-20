#include "Shape.h"


void Shape::init(Point&& p1, Point&& p2, Point&& p3, Point&& p4) {
	arr_coords.resize(4);
	arr_coords[0].init(p1.get_x(), p1.get_y());
	arr_coords[1].init(p2.get_x(), p2.get_y());
	arr_coords[2].init(p3.get_x(), p3.get_y());
	arr_coords[3].init(p4.get_x(), p4.get_y());
}

void Shape::init(Point&& p1) {
	arr_coords.resize(1);
	arr_coords[0].init(p1.get_x(), p1.get_y());
}

void Shape::init(std::vector<Point>& arr_coords) {
	this->arr_coords = arr_coords;
}

void Shape::printShape(char ch, int min_x) const {
	if (arr_coords.size() == 1 && ch != ' ') //A BOMB
	{
		ch = 'B';
	}
	for (int i = 0; i < arr_coords.size(); i++) {
		arr_coords[i].draw(ch, min_x);
	}

}

void Shape::moveCoords(GameConfig::eKeys key, int min_x) {
	if (key == GameConfig::eKeys::LEFT_L_RIGHTP || key == GameConfig::eKeys::LEFT_U_RIGHTP || key == GameConfig::eKeys::RIGHT_L_RIGHTP || key == GameConfig::eKeys::RIGHT_U_RIGHTP ||
		key == GameConfig::eKeys::LEFT_L_LEFTP || key == GameConfig::eKeys::LEFT_U_LEFTP || key == GameConfig::eKeys::RIGHT_L_LEFTP || key == GameConfig::eKeys::RIGHT_U_LEFTP)
	{
		if (!isMoveValid(key, min_x))
			key = (GameConfig::eKeys)0;
	}
	for (int i = 0; i < arr_coords.size(); i++) {
		arr_coords[i].move(key, min_x);
	}
}

bool Shape::isMoveValid(GameConfig::eKeys key, int min_x) const {
	bool is_valid = true;

	switch (key)
	{
	case GameConfig::eKeys::LEFT_L_LEFTP:
	case GameConfig::eKeys::LEFT_U_LEFTP:
	case GameConfig::eKeys::LEFT_L_RIGHTP:
	case GameConfig::eKeys::LEFT_U_RIGHTP:
		for (int i = 0; i < arr_coords.size(); i++) {
			if (arr_coords[i].get_x() - 1 < 0) {
				return is_valid = false;
			}
		}
	case GameConfig::eKeys::RIGHT_L_LEFTP:
	case GameConfig::eKeys::RIGHT_U_LEFTP:
	case GameConfig::eKeys::RIGHT_L_RIGHTP:
	case GameConfig::eKeys::RIGHT_U_RIGHTP:
		for (int i = 0; i < arr_coords.size(); i++) {
			if (arr_coords[i].get_x() + 1 > GameConfig::GAME_WIDTH - 1) {
				return is_valid = false;
			}
		}

	}

	return is_valid;
}

std::vector<Point> Shape::getCoordsArr() const {
	return arr_coords;

}

Shape getLowerShape(Shape& s1, Shape& s2) {

	std::vector<Point> s1_coords = s1.getCoordsArr();
	std::vector<Point> s2_coords = s2.getCoordsArr();

	if (s1_coords[0].get_y() == s2_coords[0].get_y())
	{
		int num_X_in_s1 = s1.getNumOfXInLowestY();
		int num_X_in_s2 = s2.getNumOfXInLowestY();
		if (num_X_in_s1 > num_X_in_s2)
		{
			return s1;
		}
		else if (num_X_in_s1 < num_X_in_s2)
		{
			return s2;
		}
		else if (abs(s1_coords[0].get_x() - 5) <= abs(s2_coords[0].get_x() - 5))
		{
			return s1;
		}
		else
		{
			return s2;
		}
	}
	else if (s1_coords[0].get_y() > s2_coords[0].get_y())
	{
		return s1;
	}
	else
	{
		return s2;
	}
};

bool isSameShape(Shape& s1, Shape& s2) {
	bool isSame = true;

	for (int i = 0; i < s1.arr_coords.size(); i++)
	{
		if (s1.arr_coords[i].get_x() != s2.arr_coords[i].get_x() || s1.arr_coords[i].get_y() != s2.arr_coords[i].get_y())
		{
			isSame = false;
			break;
		}
	}

	return isSame;
};

int Shape::getNumOfXInLowestY() {
	std::vector<Point> s_coords = this->getCoordsArr();
	int y = s_coords[0].get_y();
	int counter = 1;
	for (int i = 1; i < s_coords.size(); i++) {
		if (s_coords[i].get_y() == y) {
			counter++;
		}
	}
	return counter;

}