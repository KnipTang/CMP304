#include "TicTacToeNode.h"
#include <iostream>


// general functions

BOARD_SQUARE_STATE getOppositeMove(BOARD_SQUARE_STATE state)
{
	// Flip to the other player
	if (state == BOARD_SQUARE_STATE::CIRCLE)
	{
		return BOARD_SQUARE_STATE::CROSS;
	}
	else if (state == BOARD_SQUARE_STATE::CROSS)
	{
		return BOARD_SQUARE_STATE::CIRCLE;
	}
	else
		return BOARD_SQUARE_STATE::NONE;
}

char printNodeState(BOARD_SQUARE_STATE printState)
{
	// Print characters for specific states
	switch (printState)
	{
	case BOARD_SQUARE_STATE::NONE:
		return '.';
	case BOARD_SQUARE_STATE::CROSS:
		return 'X';
	case BOARD_SQUARE_STATE::CIRCLE:
		return 'O';
	}

	return ' ';
}



// class functions

TicTacToeNode::TicTacToeNode() 
{
	isEndState = false;
	parent = nullptr;
	ranking = 0;
	activePlayer = BOARD_SQUARE_STATE::NONE;

}

TicTacToeNode::~TicTacToeNode()
{
	// parent will be deleted by its parent so we don't need to clean it up here
	parent = nullptr;

	for (auto branch : branches)
	{
		delete branch;
	}
	branches.clear();
	availableMoves.clear();

}

/**
*  setGameState will set the game state for the node, as well as calling generatePossibleMoves to update status 
*/ 

void TicTacToeNode::setGameState(GameState newWorldState)
{
	worldState = newWorldState;
	generatePossibleMoves();
}


/**
*  generatePossibleMoves will calculate the possible mvoes from this node and set the isEndState variable appropriately
*  should only be called once when node's game state is defined
*/
void TicTacToeNode::generatePossibleMoves()
{
		
	availableMoves = worldState.getPossibleMoves();

	if (availableMoves.size() == 0)
		isEndState = true;

	if (worldState.checkWin() != BOARD_SQUARE_STATE::NONE)
		isEndState = true;
}


/*
* Select - will perform the Select step of the MCTS algorithm
*  will select down a path according to the selection policy until leaf is found 
*/
TicTacToeNode* TicTacToeNode::Select()
{

	
	// if there are no child nodes, we expand this node
	if (branches.size() == 0  || availableMoves.size() > 0)
		return this;
	else
	{

		int randomBranch = rand() % branches.size();
		return branches[randomBranch]->Select();

	}
}

/*
* Expand  - will perform the Expansion step of the MCTS algorithm
* will add a new node by randomly selecting from all possible moves
*/
TicTacToeNode* TicTacToeNode::Expand()
{
	
	if (isEndState || availableMoves.size()==0)
		return NULL; // if this is game end state, we cannot expand
	else
	{
		// pick a random move fro, the unexplored ones
		int randomMove = rand() % availableMoves.size();
		std::pair<int, int> move = availableMoves[randomMove];

		// delete the selected move from vector
		availableMoves.erase(availableMoves.begin() + randomMove);

		// create a new child node 
		TicTacToeNode* childNode = new TicTacToeNode();
		childNode->setParent(this);

		// flip the marker to other player
		BOARD_SQUARE_STATE nextTurn = getOppositeMove(activePlayer);
		childNode->setActivePlayer(nextTurn);

		// create the new world state
		GameState newWorldState;
		newWorldState.gameBoard = this->worldState.gameBoard;
		GameAction newAction(move.first, move.second, nextTurn);

		// apply the move to the board and set the child's state
		newWorldState.setAndApplyAction(newAction);
		childNode->setGameState(newWorldState);
	
		// add the newly created node as a child of current node		
		branches.push_back(childNode);

		// reutrn node, for simulation
		return childNode;
	}

}
#/*
* Simulate  - will perform the Simulate step of the MCTS algorithm
* will play random moves until a end state is found, which will trigger BackPropagation
*/
void TicTacToeNode::Simulate(BOARD_SQUARE_STATE startingTurn)
{
	// craete a copy of the node's game state as the starting point for the simulation
	GameState copyOfGameState = getGameState();

	BOARD_SQUARE_STATE playerTurn = startingTurn;
	bool endState = false;

	// check to see if this newly expanded node is a win state 
	BOARD_SQUARE_STATE winner = copyOfGameState.checkWin();

	if (winner != BOARD_SQUARE_STATE::NONE)
	{
		// we have a winner from the expanded state
		CalcResult(winner);
		return;
	}

	// repeat until we reach an end state
	do {

		// get possible moves from the current simulation state
		std::vector<std::pair<int, int>> possibleMoves = copyOfGameState.getPossibleMoves();

		if (possibleMoves.size() == 0)
		{
			// no possible moves, game must be a draw
			endState = true;
			CalcResult(BOARD_SQUARE_STATE::NONE);
			return;

		}
		else
		{
			// pick a random move and apply it to the simulation state
			int randomMove = rand() % possibleMoves.size();
			GameAction newAction(possibleMoves[randomMove].first, possibleMoves[randomMove].second, playerTurn);
			copyOfGameState.setAndApplyAction(newAction);
			possibleMoves.clear();
		}

		// check if the last move was a winning one
		BOARD_SQUARE_STATE winner = copyOfGameState.checkWin();

		if (winner != BOARD_SQUARE_STATE::NONE)
		{
			// end state, game has been won
			CalcResult(winner);
			endState = true;
			return;
		}
	
		// flip marker for next move
		playerTurn = getOppositeMove(playerTurn);

	} while (!endState);
	

}

/*
* CalcResult will handle when the board is in a final state, either win or draw

*/

void TicTacToeNode::CalcResult(BOARD_SQUARE_STATE winner)
{

	if (winner == BOARD_SQUARE_STATE::CROSS)
	{
		Backpropagate(1); 
	}
	else if (winner == BOARD_SQUARE_STATE::CIRCLE)
	{
		Backpropagate(-1);
	}
	else 
	{
		Backpropagate(0);
	}
}

#/*
* Backpropagate  - will perform the Backpropagate step of the MCTS algorithm
* the result will be returned back up the tree branches to the root node
*/

void TicTacToeNode::Backpropagate(int result)
{

	
	ranking += result;
	// if we're not at the root, update the parent with the result
	if (this->parent != NULL)
		this->parent->Backpropagate(result);

}

/*
* FindHighestRankingChild will determine which of this node's children has the highest metric
*/

TicTacToeNode* TicTacToeNode::FindHighestRankingChild(bool report)
{
	
	if (branches.size() == 0)
		return NULL;

	float maxRanking = 0;
	int maxIndex = 0;

	for (int i = 0; i < branches.size(); i++)
	{
		if (branches[i]->getRanking() > maxRanking)
		{
			maxIndex = i;
			maxRanking = branches[i]->getRanking();
		}
	}

	return branches[maxIndex];
}

#/*
* resetNode will return the node to its default values
*/

void TicTacToeNode::resetNode()
{
	branches.clear();
	ranking = 0;
	availableMoves.clear();
}