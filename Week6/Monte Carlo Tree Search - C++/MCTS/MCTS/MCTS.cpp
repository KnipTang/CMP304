

#include <iostream>
#include "GameBoard.h"
#include "TicTacToeNode.h"
using namespace std;

const int MAX_RUNS = 5000;

bool validatePosition(int x, int y, GameState gameState)
{
    if (x < 0 || x >2)
    {
        cout << "Invlid X: Enter 0,1 or 2" << endl;
        return false;
    }

    if (x < 0 || x >2)
    {
        cout << "Invlid Y: Enter 0,1 or 2" << endl;
        return false;
    }

    if (gameState.gameBoard.board[x][y] != BOARD_SQUARE_STATE::NONE)
    {
        cout << "Invlid Move: Select Empty Position" << endl;
        return false;
    }

    return true;
}




int main()
{

    cout << "*** Tic Tac Toe ***" << endl;
    
    // define the markers used by the AI and the player
    BOARD_SQUARE_STATE aiMarker = BOARD_SQUARE_STATE::CROSS;
    BOARD_SQUARE_STATE playerMarker = BOARD_SQUARE_STATE::CIRCLE;
    
    // creeate the initial board and root node for the tree
    GameState mainGameState;
    TicTacToeNode* rootNode = new TicTacToeNode();



    bool gameOver = false;

    do {

        cout << "AI is thinking...." << endl;
        rootNode->setActivePlayer(playerMarker); // the AI will move first from empty state
        rootNode->setGameState(mainGameState);

        // define a cmount
        int runCount = 0;


        // Apply the MCTS algorithm to determine the AI's move
        // - will run for maximum of MAX_RUNS iterations
        do {

            // Select - choose a node that will be expanded
            TicTacToeNode* selectedNode = rootNode->Select();

            // Expand - expand the tree from this node
            TicTacToeNode* expandedNode = selectedNode->Expand();

            // expandedNode will be NULL if it's a leaf node and simulation is not possible
            if (!expandedNode == NULL)
            {
                // Simulate & Backpropagate - Simulate to an end point, startin with aiMarker turn. 
                //  - then back propagate the result to the root node
                expandedNode->Simulate(aiMarker);
            }
      
            runCount++;
            
        } while (runCount < MAX_RUNS);



        // perform the action - find child node with highest ranking
        TicTacToeNode* highestChild = rootNode->FindHighestRankingChild(true);
        GameAction bestAction = highestChild->getGameState().gameAction;
        bestAction.playerMove = aiMarker;
        std::cout << "The AI selected move is " << bestAction.x << " " << bestAction.y << std::endl;
    
        // update the main main state with the AI's move
        mainGameState.setAndApplyAction(bestAction);
        mainGameState.printBoard();

        
        // check to see if the AI's move won the match
        // if so, game's over
        BOARD_SQUARE_STATE winner = mainGameState.checkWin();

        if (winner == BOARD_SQUARE_STATE::CIRCLE)
        {
            gameOver = true;
            cout << "CIRCLE WINS!" << endl;
            break;
        }
        else  if (winner == BOARD_SQUARE_STATE::CROSS)
        {
            gameOver = true;
            cout << "CROSS WINS!" << endl;
            break;
        }

        if (mainGameState.getPossibleMoves().size() == 0)
        {
            gameOver = true;
            cout << "IT'S A DRAW" << endl;
            break;
        }

        cout << "Make your move...." << endl;


        // Get the user to enter their X and Y co-ords
        bool validMove = true;
        int x = -1, y = -1;
        GameAction playerAction;

        do {

            x = -1, y = -1;
            cout << "Enter your x position: ";
            cin >> x;

            cout << "Enter your y position: ";
            cin >> y;

            // validate the numerical input 
            validMove = validatePosition(x, y, mainGameState);


        } while (!validMove);

        //apply the player's move to the board
        playerAction.x = x;
        playerAction.y = y;
        playerAction.playerMove = playerMarker;

        mainGameState.setAndApplyAction(playerAction);
        mainGameState.printBoard();


        // check to see if the player's move won the match
        // if so, game's over
        winner = mainGameState.checkWin();

        if (winner == BOARD_SQUARE_STATE::CIRCLE)
        {
            gameOver = true;
            cout << "CIRCLE WINS!" << endl;
        }else  if (winner == BOARD_SQUARE_STATE::CROSS)
        {
            gameOver = true;
            cout << "CROSS WINS!" << endl;
        }

        // reset the root node ready for next turn
        rootNode->resetNode();


    

    } while (!gameOver);


    cout << "GAME OVER!" << endl;

}


