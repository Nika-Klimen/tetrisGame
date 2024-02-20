#include <iostream>
using namespace std;

#include "Board.h"
#include "General.h"

void Board::drawBorder(int min_y) const {
	for (int col = min_x; col < GameConfig::GAME_WIDTH + min_x; col++)
	{
		gotoxy(col, min_y - 1);
		cout << "-";

		gotoxy(col, GameConfig::GAME_HEIGHT + min_y);
		cout << "-";
	}

	for (int row = min_y - 1; row <= GameConfig::GAME_HEIGHT + min_y; row++)
	{
		gotoxy(min_x - 1, row);
		cout << "|";

		gotoxy(GameConfig::GAME_WIDTH + min_x, row);
		cout << "|";
	}
}

void Board::initBoard(int x) {
	min_x = x;
	for (int row = 0; row < GameConfig::GAME_HEIGHT; row++) {
		for (int col = 0; col < GameConfig::GAME_WIDTH; col++) {
			game_arr[row][col] = ' ';
		}
	}
}

void Board::printBoard(int min_y) const {
	for (int row = 0; row < GameConfig::GAME_HEIGHT; row++) {
		for (int col = 0; col < GameConfig::GAME_WIDTH; col++) {
			gotoxy(col + min_x, row + min_y);
			cout << game_arr[row][col];
		}
	}
}

bool Board::checkIfHitTheFloor(Shapes& curr_shape) const {
	std::vector<Point> coords_arr = curr_shape.getShape().getCoordsArr();

	for (int i = 0; i < coords_arr.size(); i++) {

		int x = coords_arr[i].get_x();
		int y = coords_arr[i].get_y();
		if (y >= GameConfig::GAME_HEIGHT - 1) {
			return true;
		}
		if (game_arr[y + 1][x] == '*') {
			return true;
		}
	}

	return false;
}

void Board::insertShapeToBoard(Shapes& curr_shape) {
	std::vector<Point> coords_arr = curr_shape.getShape().getCoordsArr();
	if (coords_arr.size() == 1) {
		explode(coords_arr);
	}
	else
	{
		for (int i = 0; i < coords_arr.size(); i++) {

			int x = coords_arr[i].get_x();
			int y = coords_arr[i].get_y();

			game_arr[y][x] = '*';
		}
	}
}

void Board::insertFloatingShapeToBoard(Shapes& curr_shape) {
	std::vector<Point> coords_arr = curr_shape.getShape().getCoordsArr();

	for (int i = 0; i < coords_arr.size(); i++) {

		int x = coords_arr[i].get_x();
		int y = coords_arr[i].get_y();

		game_arr[y][x] = '*';
	}

}

void Board::explode(std::vector<Point>& coords_arr) {

	int x = coords_arr[0].get_x();
	int y = coords_arr[0].get_y();
	int new_x = (x - GameConfig::EXPLODE_RANGE) < 0 ? 0 : x - GameConfig::EXPLODE_RANGE;
	int new_y = (y - GameConfig::EXPLODE_RANGE) < 0 ? 0 : y - GameConfig::EXPLODE_RANGE;

	for (int col = new_x; col <= (x + GameConfig::EXPLODE_RANGE) && (col < GameConfig::GAME_WIDTH); col++) {
		for (int row = new_y; row <= (y + GameConfig::EXPLODE_RANGE) && (row < GameConfig::GAME_HEIGHT); row++) {
			game_arr[row][col] = ' ';
		}
	}
	printBoard(GameConfig::MIN_Y);
	detactFloatingShapesAndDrop();
}

bool Board::checkIfGameStillOn() const {
	for (int col = 0; col < GameConfig::GAME_WIDTH; col++)
	{
		if (game_arr[0][col] != ' ')
		{
			return false;
		}
	}
	return true;
}

void Board::DeleteLastRow(int deletd_row) {
	int row = deletd_row;

	for (int col = 0; col < GameConfig::GAME_WIDTH; col++) {
		game_arr[row][col] = ' ';
	}
}

void Board::DropDownAllTheBoard(int deletd_row) {
	for (int row = deletd_row; row > 0; row--) {
		for (int col = GameConfig::GAME_WIDTH - 1; col >= 0; col--) {
			game_arr[row][col] = game_arr[row - 1][col];
		}
	}

	int row = 0;

	for (int col = 0; col < GameConfig::GAME_WIDTH; col++) {
		game_arr[row][col] = ' ';
	}
}

void Board::detactAFullRowAndDelete(int min_y) {
	int row = GameConfig::GAME_HEIGHT - 1;
	while (row >= 0)
	{
		bool rowIsFull = true;
		for (int col = 0; col < GameConfig::GAME_WIDTH; col++)
		{
			if (game_arr[row][col] == ' ')
			{
				rowIsFull = false;
				break;
			}
		}
		if (rowIsFull) {
			DeleteLastRow(row);
			Sleep(GameConfig::SLEEP);
			printBoard(min_y);
			Sleep(GameConfig::SLEEP);
			DropDownAllTheBoard(row);
			printBoard(min_y);
			Sleep(GameConfig::SLEEP);
		}
		else
			row--;
	}
}

void Board::detactFloatingShapesAndDrop()
{
	int shape_col;
	for (int row = GameConfig::GAME_HEIGHT - 2; row >= 0; row--)
	{
		int col = 0;
		while (col < GameConfig::GAME_WIDTH)
		{
			bool shape_floats = false;
			shape_col = col + 1;
			if (game_arr[row][col] == '*')
			{
				if (game_arr[row + 1][col] == ' ') {
					shape_floats = true;
				}
				else {
					while (game_arr[row][shape_col] == '*' && shape_col < GameConfig::GAME_WIDTH) {
						shape_col++;
					}
				}
			}
			while (shape_floats && shape_col < GameConfig::GAME_WIDTH - 1)
			{
				if ((game_arr[row][shape_col] == '*' && game_arr[row + 1][shape_col] == ' '))
				{
					shape_floats = true;
					shape_col++;
				}
				else if ((game_arr[row][shape_col] == ' '))
				{
					break;
				}
				else
				{
					shape_floats = false;
				}
			}
			if (shape_floats) {
				std::vector<Point> arr_coords;
				for (int x = col; x < shape_col; x++) {
					arr_coords.push_back(Point(x, row));
					game_arr[row][x] = ' ';
				}
				Shapes shape_to_drop;
				shape_to_drop.initRandomShape(arr_coords);
				bool shape_hit_floor = false;
				while (!shape_hit_floor) {
					shape_to_drop.moveShape((GameConfig::eKeys)0, min_x); //MOVE DOWN ONLY
					shape_hit_floor = checkIfHitTheFloor(shape_to_drop);
				}
				insertFloatingShapeToBoard(shape_to_drop);

			}
			col = shape_col;
		}

	}
}