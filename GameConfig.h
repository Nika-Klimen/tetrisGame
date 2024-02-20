
#ifndef __GAME_CONFIG_H
#define __GAME_CONFIG_H

class GameConfig
{
public:
	enum class eKeys {
		LEFT_L_LEFTP = 'a', LEFT_U_LEFTP = 'A', RIGHT_L_LEFTP = 'd', RIGHT_U_LEFTP = 'D', DROP_L_LEFTP = 'x', DROP_U_LEFTP = 'X', ESC = 27,
		LEFT_L_RIGHTP = 'j', LEFT_U_RIGHTP = 'J', RIGHT_L_RIGHTP = 'l', RIGHT_U_RIGHTP = 'L', DROP_L_RIGHTP = 'm', DROP_U_RIGHTP = 'M'
		, ROTATE_CLOCKWISE_L_LEFTP = 's', ROTATE_CLOCKWISE_U_LEFTP = 'S', ROTATE_COUNTER_CLOCKWISE_L_LEFTP = 'w', ROTATE_COUNTER_CLOCKWISE_U_LEFTP = 'W',
		ROTATE_CLOCKWISE_L_RIGHTP = 'k', ROTATE_CLOCKWISE_U_RIGHTP = 'K', ROTATE_COUNTER_CLOCKWISE_L_RIGHTP = 'i', ROTATE_COUNTER_CLOCKWISE_U_RIGHTP = 'I',
		START_NEW_GAME_HH = '1', START_NEW_GAME_HC = '2', START_NEW_GAME_CC = '3', CONTINUE = '4', INSTRUCTIONS = '8', EXIT = '9'
	};

	static constexpr int GAME_WIDTH = 12;
	static constexpr int GAME_HEIGHT = 18;

	static constexpr int MIN_X_MENU = 5;
	static constexpr int MIN_X_LEFT = 10;
	static constexpr int MIN_X_RIGHT = 30;
	static constexpr int MIN_Y = 3;

	static constexpr int EXIT_GAME = 0;
	static constexpr int CONTINUE_GAME = 1;
	static constexpr int NEW_GAME = 2;

	static constexpr int EXPLODE_RANGE = 3;
	static constexpr int SLEEP = 250;
	static constexpr int SLEEP_IN_DROP = 30;
	static constexpr int GOOD_PROBABILITY = 40;
	static constexpr int NOVICE_PROBABILITY = 10;
	static constexpr int BOMB_PROBABILITY = 20;
	static constexpr int SHAPE_PROBABILITY = 7;

	static constexpr char BEST = 'a';
	static constexpr char GOOD = 'b';
	static constexpr char NOVICE = 'c';
};
#endif
