#include "ComputerPlayer.h"


ComputerPlayer::ComputerPlayer(int x, char level) {

	min_x = x;
	this->level = level;
	board.initBoard(min_x);
	is_game_on = true;
	newShape();

};

Shape ComputerPlayer::FindBestPlaceToLand(Shape& curr_shape) const {
	bool hit_the_floor, move_is_valid = true;
	int x_move = -5;
	Shape temp = curr_shape;
	Shape best_landing;
	std::vector<Point> temp_coords = temp.getCoordsArr();


	for (int i = 0; i < temp_coords.size(); i++) {
		temp_coords[i].addX(x_move);
	}
	x_move++;
	Shapes temp_Shapes;
	temp_Shapes.initRandomShape(temp_coords);

	best_landing = temp_Shapes.getShape();

	while (move_is_valid) {
		hit_the_floor = false;
		while (!hit_the_floor) {
			temp_Shapes.moveShape((GameConfig::eKeys)0, min_x);
			hit_the_floor = board.checkIfHitTheFloor(temp_Shapes);
		}
		Shape temp2 = temp_Shapes.getShape();
		best_landing = getLowerShape(temp2, best_landing);

		temp = curr_shape;
		temp_coords = temp.getCoordsArr();

		for (int i = 0; i < temp_coords.size(); i++) {
			if (temp_coords[i].get_x() + x_move > GameConfig::GAME_WIDTH - 1)
			{
				move_is_valid = false;
				break;
			}

		}

		if (move_is_valid)
		{
			for (int i = 0; i < temp_coords.size(); i++) {
				temp_coords[i].addX(x_move);
			}
		}
		temp_Shapes.initRandomShape(temp_coords);
		x_move++;
	}

	return best_landing;

};

Shape ComputerPlayer::FindRandomPlaceToLand(Shape& curr_shape) const
{
	bool hit_the_floor = false;

	Shape temp = curr_shape;
	std::vector<Point> temp_coords = temp.getCoordsArr();

	for (int i = 0; i < temp_coords.size(); i++) {
		temp_coords[i].addX(-5);
	}

	Shapes temp_Shapes;
	temp_Shapes.initRandomShape(temp_coords);

	while (!hit_the_floor) {
		temp_Shapes.moveShape((GameConfig::eKeys)0, min_x);
		hit_the_floor = board.checkIfHitTheFloor(temp_Shapes);
	}

	return temp_Shapes.getShape();

}

void ComputerPlayer::FindLandingPos() {
	std::vector<move> landing_options;
	int num_of_positions = curr_shape.getNumOfPositions();
	landing_options.resize(num_of_positions);
	for (int i = 0; i < num_of_positions; i++)
	{
		Shape curr_pos = curr_shape.getShape(i);
		move best_final_move;
		switch (level)
		{
		case GameConfig::BEST:
			best_final_move.best_finel_pos = FindBestPlaceToLand(curr_pos);
		case GameConfig::GOOD:
			if (move_count % GameConfig::GOOD_PROBABILITY == 0)
				best_final_move.best_finel_pos = FindRandomPlaceToLand(curr_pos);
			else
				best_final_move.best_finel_pos = FindBestPlaceToLand(curr_pos);
		case GameConfig::NOVICE:
			if (move_count % GameConfig::NOVICE_PROBABILITY == 0)
				best_final_move.best_finel_pos = FindRandomPlaceToLand(curr_pos);
			else
				best_final_move.best_finel_pos = FindBestPlaceToLand(curr_pos);
		}
		best_final_move.steps_x = curr_pos.getCoordsArr()[0].get_x() - best_final_move.best_finel_pos.getCoordsArr()[0].get_x();
		best_final_move.steps_y = curr_pos.getCoordsArr()[0].get_y() - best_final_move.best_finel_pos.getCoordsArr()[0].get_y();
		landing_options[i] = best_final_move;
	}
	landing_pos = FindMove(landing_options);

};

move ComputerPlayer::FindMove(std::vector<move> landing_options) {

	move wanted_move = landing_options[0];
	int wanted_pos = 0;
	wanted_move.rotation = 0;
	for (int i = 1; i < landing_options.size(); i++) {
		wanted_move.best_finel_pos = getLowerShape(wanted_move.best_finel_pos, landing_options[i].best_finel_pos);
		if (isSameShape(wanted_move.best_finel_pos, landing_options[i].best_finel_pos)) {
			wanted_move.steps_x = landing_options[i].steps_x;
			wanted_move.steps_y = landing_options[i].steps_y;
			wanted_move.rotation = i;
		}
	}
	return wanted_move;
};

void ComputerPlayer::Move() {
	curr_shape.printCurrPos('*', min_x);
	Sleep(GameConfig::SLEEP);
	curr_shape.printCurrPos(' ', min_x);
	if (!board.checkIfHitTheFloor(curr_shape))
	{
		//////////////
		if (landing_pos.rotation != 0)
		{
			curr_shape.UpdateCurrPos();
			landing_pos.rotation--;
		}
		if (landing_pos.steps_x == 0) {
			curr_shape.moveShape((GameConfig::eKeys)0, min_x);
		}
		else if (landing_pos.steps_x > 0) {
			if (min_x == GameConfig::MIN_X_LEFT) {
				curr_shape.moveShape(GameConfig::eKeys::LEFT_L_LEFTP, min_x);
			}
			else {
				curr_shape.moveShape(GameConfig::eKeys::LEFT_L_RIGHTP, min_x);

			}
			landing_pos.steps_x--;
		}
		else {
			if (min_x == GameConfig::MIN_X_LEFT) {
				curr_shape.moveShape(GameConfig::eKeys::RIGHT_L_LEFTP, min_x);
			}
			else {
				curr_shape.moveShape(GameConfig::eKeys::RIGHT_L_RIGHTP, min_x);

			}
			landing_pos.steps_x++;
		}
		curr_shape.printCurrPos('*', min_x);
	}
	else
	{
		board.insertShapeToBoard(curr_shape);
	}

};

void ComputerPlayer::newShape() {
	move_count++;
	curr_shape.init_shape();
	shape_still_moves = true;
	FindLandingPos();
};

