#pragma once
#include <Windows.h>
#include <vector>

#include "Player.h"
#include "Shape.h"
#include "Shapes.h"
#include "Board.h"


struct move {
	Shape best_finel_pos;
	int steps_x;
	int steps_y;
	int rotation;
};

class ComputerPlayer :public Player
{
private:

	struct move landing_pos;
	int move_count = 0;
	char level;


public:
	Shape FindBestPlaceToLand(Shape& curr_shape) const;
	void FindLandingPos();
	struct move FindMove(std::vector<struct move> landing_options);
	void Move();
	ComputerPlayer(int x, char level);
	void  newShape();
	void KeyPressed(char key) {};
	static ComputerPlayer* newComputerPlayer(int min_x, char level) {
		return new ComputerPlayer(min_x, level);
	}
	Shape FindRandomPlaceToLand(Shape& curr_shape) const;

};