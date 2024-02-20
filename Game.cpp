#include "Game.h"


void startGame(Board& b_left, Board& b_right) {

	gotoxy(GameConfig::MIN_X_RIGHT + GameConfig::MIN_X_LEFT + 10, GameConfig::MIN_Y);
	cout << "PRESS ESC TO VIEW MENU";

	b_left.initBoard(GameConfig::MIN_X_LEFT);
	b_right.initBoard(GameConfig::MIN_X_RIGHT);

	b_left.drawBorder();
	b_right.drawBorder();
}

void continueGame(Board& b_left, Board& b_right) {

	gotoxy(GameConfig::MIN_X_RIGHT + GameConfig::MIN_X_LEFT + 10, GameConfig::MIN_Y);
	cout << "PRESS ESC TO VIEW MENU";

	b_left.drawBorder();
	b_right.drawBorder();
	b_left.printBoard();
	b_right.printBoard();
}

void newrun() {

	Player* left_player = nullptr, * right_player = nullptr;
	int game_status;
	bool stop_game = false;

	game_status = menu(false, left_player, right_player);
	system("cls");
	left_player->printBoard();
	right_player->printBoard();

	while (left_player->getIsGameOn() && right_player->getIsGameOn() && !stop_game) {

		left_player->printBoard();
		right_player->printBoard();

		if (!left_player->getShapeStillMoves()) {
			left_player->newShape();
		}
		if (!right_player->getShapeStillMoves()) {
			right_player->newShape();
		}
		while (left_player->getShapeStillMoves() && right_player->getShapeStillMoves()) {

			int key = 0;
			if (_kbhit())
			{
				key = _getch();
				if ((GameConfig::eKeys)key == GameConfig::eKeys::ESC)
				{
					game_status = pausedGame(stop_game, left_player, right_player, true);
					if (game_status == GameConfig::EXIT_GAME || game_status == GameConfig::NEW_GAME) {
						break;
					}
				}
				left_player->KeyPressed(key);
				right_player->KeyPressed(key);

			}
			cleanBuffer();

			left_player->Move();
			right_player->Move();

			left_player->checkIfShapeStillMoves();
			right_player->checkIfShapeStillMoves();

		}


		if (left_player->getIsGameOn() == false || right_player->getIsGameOn() == false)
		{
			announceWinner(left_player, right_player);
			gotoxy(GameConfig::MIN_X_MENU, GameConfig::MIN_Y + 2);
			cout << "PRESS ANY KEY TO GET TO THE MENU";
			if (_getch())
			{
				game_status = pausedGame(stop_game, left_player, right_player, false);
				if (stop_game) {
					break;
				}
			}
		}

	}

	system("cls");
	delete left_player;
	delete right_player;
}

int pausedGame(bool& stop_game, Player*& left_player, Player*& right_player, bool is_game_paused)
{
	int game_status = menu(is_game_paused, left_player, right_player);
	if (game_status == GameConfig::EXIT_GAME)
	{
		system("cls");
		stop_game = true;
	}
	else if (game_status == GameConfig::CONTINUE_GAME)
	{
		system("cls");
		left_player->printBoard();
		right_player->printBoard();
		stop_game = false;
	}
	else //new game
	{
		system("cls");
		stop_game = false;
	}
	return game_status;
}

void announceWinner(Player*& left_player, Player*& right_player) {

	cleanBuffer();
	system("cls");
	if (left_player->getIsGameOn() == false)
	{
		gotoxy(GameConfig::MIN_X_MENU, GameConfig::MIN_Y);
		cout << "THE WINNER IS RIGHT PLAYER !!!";
	}
	else if (right_player->getIsGameOn() == false)
	{
		gotoxy(GameConfig::MIN_X_MENU, GameConfig::MIN_Y);
		cout << "THE WINNER IS LEFT PLAYER !!!";
	}
	else
	{
		gotoxy(GameConfig::MIN_X_MENU, GameConfig::MIN_Y);
		cout << "ITS A TIE";
	}
}