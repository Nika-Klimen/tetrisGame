#include <windows.h> // for gotoxy
#include <process.h> // for system
#include <iostream>
#include <conio.h>

using namespace std;

void gotoxy(int x, int y) {
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

void cleanBuffer() {
	while (_kbhit()) {
		_getch();
	}
}