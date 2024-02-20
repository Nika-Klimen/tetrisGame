#include "Player.h"

void Player::checkIfShapeStillMoves() {
	shape_still_moves = !board.checkIfHitTheFloor(curr_shape) && shape_still_moves;
	if (!shape_still_moves)
	{
		board.insertShapeToBoard(curr_shape);

		board.detactAFullRowAndDelete();

		is_game_on = board.checkIfGameStillOn();
		if (!is_game_on)
		{
			shape_still_moves = false;
		}
	}
};

bool  Player::getIsGameOn() const {
	return is_game_on;
};

bool  Player::getShapeStillMoves() const {
	return shape_still_moves;
};

void Player::printBoard() const {
	board.printBoard();
	board.drawBorder();
}