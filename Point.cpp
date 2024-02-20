#include "Point.h"
#include "GameConfig.h"
#include "General.h"

#include <iostream>
#include <Windows.h>
using namespace std;

void Point::init(int x, int y) {
	this->x = x;
	this->y = y;
	diff_x = 0;
	diff_y = 1;
}

void Point::draw(char ch, int min_x) const {
	gotoxy(x + min_x, y + GameConfig::MIN_Y);
	cout << ch;
}

void Point::move(GameConfig::eKeys key, int min_x) {
	if (min_x == GameConfig::MIN_X_LEFT)
	{
		switch (key)
		{
		case GameConfig::eKeys::LEFT_L_LEFTP:
		case GameConfig::eKeys::LEFT_U_LEFTP:
			diff_x = -1;
			break;
		case GameConfig::eKeys::RIGHT_L_LEFTP:
		case GameConfig::eKeys::RIGHT_U_LEFTP:
			diff_x = 1;
			break;
		}
	}
	else
	{
		switch (key)
		{
		case GameConfig::eKeys::LEFT_L_RIGHTP:
		case GameConfig::eKeys::LEFT_U_RIGHTP:
			diff_x = -1;
			break;
		case GameConfig::eKeys::RIGHT_L_RIGHTP:
		case GameConfig::eKeys::RIGHT_U_RIGHTP:
			diff_x = 1;
			break;
		}
	}

	x += diff_x;

	y += diff_y;
	if (y > GameConfig::GAME_HEIGHT - 1)
		y -= diff_y;


	diff_x = 0;
	diff_y = 1;
}

int Point::get_x() const {
	return x;
}

int Point::get_y() const {
	return y;
}