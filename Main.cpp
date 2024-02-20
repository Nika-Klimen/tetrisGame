#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#include "Point.h"
#include "Shapes.h"
#include "Shapes.h"
#include "Board.h"
#include "General.h"
#include "Game.h"


int main() {

	srand((time(NULL)));

	newrun();

	gotoxy(0, GameConfig::MIN_Y + GameConfig::GAME_HEIGHT + 5);
}