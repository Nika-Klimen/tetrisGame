#pragma once
#include <Windows.h>
#include <vector>

#include "Player.h"
#include "Shape.h"
#include "Shapes.h"
#include "Board.h"

class HumanPlayer :public Player
{
private:
	int keyPressed;

public:
	void Move();
	HumanPlayer(int x);
	void newShape();
	void KeyPressed(char key);
	static HumanPlayer* newHumanPlayer(int min_x) {
		return new HumanPlayer(min_x);
	}
	void drop(int min_x, Board& board, Shapes& curr_shape);

};