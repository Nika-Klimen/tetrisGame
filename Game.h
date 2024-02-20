#pragma once
#include <Windows.h>
#include <iostream>
#include <conio.h>

#include "Board.h"
#include "Shapes.h"
#include "Menu.h"
#include "ComputerPlayer.h"
#include "Player.h"
#include "HumanPlayer.h"


void run();
void startGame(Board& b_left, Board& b_right);
void continueGame(Board& b_left, Board& b_right);
void runComputerVsComputer();
void newrun();
int pausedGame(bool& stop_game, Player*& left_player, Player*& right_player, bool is_game_paused);
void announceWinner(Player*& left_player, Player*& right_player);