#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(int x) {
	min_x = x;
	curr_shape.init_shape();
	shape_still_moves = true;
	board.initBoard(min_x);
	is_game_on = true;
}

void HumanPlayer::newShape() {
	curr_shape.init_shape();
	shape_still_moves = true;
}

void HumanPlayer::Move() {
	curr_shape.printCurrPos('*', min_x);
	Sleep(GameConfig::SLEEP);
	curr_shape.printCurrPos(' ', min_x);

	if (keyPressed == (int)GameConfig::eKeys::ROTATE_CLOCKWISE_L_LEFTP || keyPressed == (int)GameConfig::eKeys::ROTATE_CLOCKWISE_U_LEFTP || keyPressed == (int)GameConfig::eKeys::ROTATE_COUNTER_CLOCKWISE_L_LEFTP ||
		keyPressed == (int)GameConfig::eKeys::ROTATE_COUNTER_CLOCKWISE_U_LEFTP || keyPressed == (int)GameConfig::eKeys::ROTATE_CLOCKWISE_L_RIGHTP || keyPressed == (int)GameConfig::eKeys::ROTATE_CLOCKWISE_U_RIGHTP ||
		keyPressed == (int)GameConfig::eKeys::ROTATE_COUNTER_CLOCKWISE_L_RIGHTP || keyPressed == (int)GameConfig::eKeys::ROTATE_COUNTER_CLOCKWISE_U_RIGHTP)
	{
		curr_shape.rotate((GameConfig::eKeys)keyPressed, min_x);
	}
	if ((keyPressed == (int)GameConfig::eKeys::DROP_L_LEFTP || keyPressed == (int)GameConfig::eKeys::DROP_U_LEFTP) && min_x == GameConfig::MIN_X_LEFT)
	{
		curr_shape.printCurrPos('*', min_x);
		drop(min_x, board, curr_shape);
		shape_still_moves = false;
		curr_shape.printCurrPos(' ', GameConfig::MIN_X_LEFT);
	}
	if ((keyPressed == (int)GameConfig::eKeys::DROP_L_RIGHTP || keyPressed == (int)GameConfig::eKeys::DROP_U_RIGHTP) && min_x == GameConfig::MIN_X_RIGHT)
	{
		curr_shape.printCurrPos('*', min_x);
		drop(min_x, board, curr_shape);
		shape_still_moves = false;
		curr_shape.printCurrPos(' ', GameConfig::MIN_X_LEFT);
	}


	if (!board.checkIfHitTheFloor(curr_shape))
	{
		curr_shape.moveShape((GameConfig::eKeys)keyPressed, min_x);
	}
	else
	{
		board.insertShapeToBoard(curr_shape);
		keyPressed = 0;
		return;
	}

	curr_shape.printCurrPos('*', min_x);
	Sleep(GameConfig::SLEEP);
	keyPressed = 0;
}

void HumanPlayer::drop(int min_x, Board& board, Shapes& curr_shape) {
	bool check_if_droped = false;

	while (!check_if_droped) {
		curr_shape.printCurrPos('*', min_x);
		Sleep(GameConfig::SLEEP_IN_DROP);
		curr_shape.printCurrPos(' ', min_x);
		check_if_droped = board.checkIfHitTheFloor(curr_shape);
		if (check_if_droped) {
			break;
		}
		else
		{
			curr_shape.moveShape((GameConfig::eKeys)0, min_x);
		}
	}
}

void HumanPlayer::KeyPressed(char key) {
	keyPressed = key;
}
