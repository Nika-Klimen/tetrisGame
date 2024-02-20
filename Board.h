#pragma once
#include <Windows.h>
#include <vector>
#include "GameConfig.h"
#include "Shapes.h"

class Board
{
private:
	char game_arr[GameConfig::GAME_HEIGHT][GameConfig::GAME_WIDTH];
	int min_x;
public:

	void initBoard(int x);
	void drawBorder(int min_y = GameConfig::MIN_Y) const;
	void printBoard(int min_y = GameConfig::MIN_Y) const;
	bool checkIfHitTheFloor(Shapes& curr_shape) const;
	void insertShapeToBoard(Shapes& curr_shape);
	bool checkIfGameStillOn() const;
	void DeleteLastRow(int deletd_row);
	void DropDownAllTheBoard(int deletd_row);
	void detactAFullRowAndDelete(int min_y = GameConfig::MIN_Y);
	void explode(std::vector<Point>& coords_arr);
	void detactFloatingShapesAndDrop();
	void insertFloatingShapeToBoard(Shapes& curr_shape);

};

