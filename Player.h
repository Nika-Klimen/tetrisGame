#pragma once
#include "Shapes.h"
#include "Shape.h"
#include "Board.h"

class Player
{
protected:
	Shapes curr_shape;
	bool shape_still_moves;
	Board board;
	bool is_game_on;
	int min_x;

public:
	virtual void Move() = 0;
	bool getIsGameOn() const;
	bool getShapeStillMoves() const;
	virtual void KeyPressed(char key) = 0;
	void checkIfShapeStillMoves();
	virtual void  newShape() = 0;
	void printBoard() const;
	virtual ~Player() {};
};
