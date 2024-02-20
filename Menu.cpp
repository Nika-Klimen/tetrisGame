#include "Menu.h"


void printMenu(bool is_game_paused)
{
	string menu[] = { "(1) Start a new game - Human VS Human","(2) Start a new game - Human VS Computer" ,"(3) Start a new game - Computer VS Computer","(4) Continue a paused game" ,"(8) Present instructions and keys" ,"(9) EXIT" };
	int row = 0;
	for (int i = 0; i < size(menu); i++)
	{
		if (!is_game_paused && i == 3)
		{
			continue;
		}
		else
		{
			gotoxy(GameConfig::MIN_X_MENU, GameConfig::MIN_Y + row);
			cout << menu[i] << endl;
			row++;
		}

	}
}

void printInstructionsAndKeys() {
	string instructions[] = { "Goal:",
	"Clear lines by placing falling tetriminos", "strategically on a grid.",
	"the first player who gets their blocks", "stack up to the top of the board loses!",
	"Gameplay:",
	"- Clear lines to score points.",
	"- Stack tetriminos without reaching the","top to continue playing.",
	"- Bomb: When a bomb reaches its position on top of any other square,",
	"it explodes and all squares that are in a block distance of",
	"4 squares disappear ",
	"_______________________",
	"Keys - Left player:",
	"-LEFT = 'a' or 'A'",
	"-RIGHT = 'd' or 'D'",
	"-ROTATE clockwise - 's' or 'S'",
	"-ROTATE counterclockwise = 'w' or 'W'" ,
	"-DROP - 'x' or 'X'",
	"_______________________",
	"Keys - Right player:",
	"-LEFT = 'j' or 'J'",
	"-RIGHT = 'l' or 'L'",
	"-ROTATE clockwise - 'k' or 'K'",
	"-ROTATE counterclockwise = 'i' or 'I'" ,
	"-DROP - 'm' or 'M'",
	"_______________________",
	"PRESS ANY KEY TO GO BACK TO MENU" };

	for (int i = 0; i < size(instructions); i++)
	{
		gotoxy(GameConfig::MIN_X_MENU, i);
		cout << instructions[i] << endl;
	}

}

int menu(bool is_game_paused, Player*& left_player, Player*& right_player) {
	int keyPressed = 0;
	char level;

	system("cls");
	printMenu(is_game_paused);

	keyPressed = _getch();

	switch ((GameConfig::eKeys)keyPressed)
	{
	case GameConfig::eKeys::START_NEW_GAME_HH:
		left_player = HumanPlayer::newHumanPlayer(GameConfig::MIN_X_LEFT);
		right_player = HumanPlayer::newHumanPlayer(GameConfig::MIN_X_RIGHT);
		return GameConfig::NEW_GAME;
		break;
	case GameConfig::eKeys::START_NEW_GAME_HC:
		level = printLevels(GameConfig::MIN_X_RIGHT);
		left_player = HumanPlayer::newHumanPlayer(GameConfig::MIN_X_LEFT);
		right_player = ComputerPlayer::newComputerPlayer(GameConfig::MIN_X_RIGHT, level);
		return GameConfig::NEW_GAME;
		break;
	case GameConfig::eKeys::START_NEW_GAME_CC:
		level = printLevels(GameConfig::MIN_X_LEFT);
		left_player = ComputerPlayer::newComputerPlayer(GameConfig::MIN_X_LEFT, level);
		level = printLevels(GameConfig::MIN_X_RIGHT);
		right_player = ComputerPlayer::newComputerPlayer(GameConfig::MIN_X_RIGHT, level);
		return GameConfig::NEW_GAME;
		break;
	case GameConfig::eKeys::CONTINUE:
		return GameConfig::CONTINUE_GAME;
		break;
	case GameConfig::eKeys::INSTRUCTIONS:
		system("cls");
		printInstructionsAndKeys();
		keyPressed = _getch();
		if (keyPressed)
		{
			return menu(is_game_paused, left_player, right_player);
			break;
		}
	case GameConfig::eKeys::EXIT:
		return GameConfig::EXIT_GAME;
	}

	system("cls");

	return true;
}

char printLevels(int min_x) {
	system("cls");
	int row = -1;
	gotoxy(GameConfig::MIN_X_MENU, GameConfig::MIN_Y + row);

	cout << "Select the level on the ";
	if (min_x == GameConfig::MIN_X_LEFT) {

		cout << "left side" << endl;
	}
	else {
		cout << "right side" << endl;

	}
	row++;

	string levels[] = { "(a) BEST ","(b) GOOD" ,"(c) NOVICE" };


	for (int i = 0; i < size(levels); i++)
	{
		gotoxy(GameConfig::MIN_X_MENU, GameConfig::MIN_Y + row);
		cout << levels[i] << endl;
		row++;
	}


	return _getch();


}

