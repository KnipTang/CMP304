#pragma once

#include <vector>
#include <stack>
#include "GameBoard.h"
#include "GameState.h"

class TicTacToeNode
{
public:
	TicTacToeNode();
	~TicTacToeNode();


	//gets and sets
	void setGameState(GameState newState);
	GameState getGameState() { return worldState; }

	bool getIsEndState() { return isEndState; }
	std::vector<TicTacToeNode*> getBranches() { return branches; }
	int getRanking() { return ranking; }	

	void setActivePlayer(BOARD_SQUARE_STATE active) { activePlayer = active; }
	BOARD_SQUARE_STATE getActivePlayer() { return activePlayer; }

	void setParent(TicTacToeNode* newParent) { parent = newParent; }


	// MCTS steps
	TicTacToeNode* Select();
	TicTacToeNode* Expand();
	void Simulate(BOARD_SQUARE_STATE playerTurn);
	void Backpropagate(int reward);

	// tree functions
	TicTacToeNode* FindHighestRankingChild(bool report);
	void resetNode();
	void CalcResult(BOARD_SQUARE_STATE winner);
	
	 

private:
	int ranking; // ranking is updated via back propagation
	std::vector<TicTacToeNode*> branches; // child nodes
	TicTacToeNode* parent; // parent node
	GameState worldState; // game state at this node
	bool isEndState; // if eitehr game is won or no moves possible
	std::vector<std::pair<int, int>> availableMoves; // unexplored branches
	BOARD_SQUARE_STATE activePlayer; // the player who moved to create this state - child nodes should use opposite marker

	void generatePossibleMoves();
};

