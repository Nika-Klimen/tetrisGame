#ifndef MENU_H
#define MENU_H

#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "GameConfig.h"
#include "General.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"

using namespace std;

void printMenu(bool is_game_paused);
void printInstructionsAndKeys();
int menu(bool is_game_paused, Player*& left_player, Player*& right_player);
void startingManu(Player* left_player, Player* right_player);
char printLevels(int min_x);

#endif