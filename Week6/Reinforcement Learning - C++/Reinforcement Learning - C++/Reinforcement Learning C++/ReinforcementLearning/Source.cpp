#include <array>
#include <utility>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

#define ACTION_NUM 3
#define STATE_NUM 3
#define PLAYER_SPEED 4

enum State { IN_RANGE = 0, TOO_FAR, TOO_CLOSE };
enum Action { WAIT = 0, MOVE_AWAY, MOVE_CLOSER };
std::array<std::array<float, ACTION_NUM>, STATE_NUM> LM = { {0} };
std::array<std::string, ACTION_NUM> action_to_string = { "WAIT", "MOVE_AWAY", "MOVE_CLOSER" };
std::array<std::string, ACTION_NUM> state_to_string = { "IN_RANGE", "TOO_FAR", "TOO_CLOSE" };







void printMatrix()
{
	using namespace std;
	cout << "LM Matrix" << endl << endl;
	for (int i = 0; i < STATE_NUM; i++)
	{
		for (int j = 0; j < ACTION_NUM; j++)
		{
			cout << "For state \"" << state_to_string[i] << "\" the action \"" << action_to_string[j] << "\" has a value of: " << LM[i][j] << endl;
		}
	}
}



int main()
{
	srand(time(NULL));

	float player_distance = 50.f;

	int iterator = 0;

	float player_move = 0.0f;

	while (player_distance > 0)
	{


		// Describe State
		// TODO 1: Store a local variable that describes the current state
		

		std::cout << "---" << std::endl;
		std::cout << "Player Distance is " << player_distance << std::endl;

		// Choose Action
		// TODO 2: Store a local variable that explains what action the AI will perform
		


		// Perform the Action
		// TODO 3: Implement the chosen action. Use a switch statement or function to manage this.
		

	
		// Calculate Reward
		// TODO 4: Calculate the reward you want to give to the AI
		

		// Update Matrix
		// TODO 5: Update the correct item the matrix with the correct reward.
		


		// TODO 6: Print out which action the AI ran. You can use a similar method to the action_to_string or state_to_string described in the printMatrix function
		

		player_move = (rand() % PLAYER_SPEED);
		player_distance -= player_move;
		std::cout << "Player has moved " << player_move << " closer..." << std::endl;
		std::this_thread::sleep_for(1000ms);
		iterator++;

		if (iterator % 100 == 0)
		{
			printMatrix();
		}

	}

	printMatrix();

	std::cin.get();
}