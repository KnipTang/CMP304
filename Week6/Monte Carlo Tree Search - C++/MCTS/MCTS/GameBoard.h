#pragma once

// define enum's and structs used in the game
enum BOARD_SQUARE_STATE { NONE, CIRCLE, CROSS };

struct GameBoard
{
	BOARD_SQUARE_STATE board[3][3]{ { BOARD_SQUARE_STATE::NONE } };
};

struct GameAction
{
	int x, y;
	BOARD_SQUARE_STATE playerMove;

public:
	GameAction(int newX, int newY, BOARD_SQUARE_STATE move)
	{
		x = newX;
		y = newY;
		playerMove = move;
	}

	GameAction()
	{
		playerMove = BOARD_SQUARE_STATE::NONE;
		x = 0;
		y = 0;
	}
	 

};

