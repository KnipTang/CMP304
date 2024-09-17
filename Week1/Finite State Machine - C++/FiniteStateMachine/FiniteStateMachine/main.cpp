#include <iostream>		
#include <thread>	 
#include <chrono>
#include <conio.h>

using namespace std::this_thread;	// sleep_for
using namespace std::chrono;			// seconds, milliseconds

using namespace std::chrono_literals;

enum class FSM_States
{
	Watch,
	StandAndBoo,
	StandAndCheer,
	FoodStall,
	SitAndEat
};

int main()
{
	bool program_running = true;

	bool enemyTeamScores = false;
	bool homeTeamScores = false;

	bool hungry = false;

	bool gotFood = false;

	auto startTime = std::chrono::high_resolution_clock().now();

	std::cout << "Starting Finite State Machine. Press ESC key to close." << std::endl;

	FSM_States currentState = FSM_States::Watch;

	do {
		switch (currentState)
		{
			case FSM_States::Watch:
				std::cout << "Watching\n";

				if(hungry)
					currentState = FSM_States::FoodStall;

				if (homeTeamScores)
				{
					currentState = FSM_States::StandAndCheer;
					homeTeamScores = false;
					startTime = std::chrono::high_resolution_clock().now();
				}
				else if (enemyTeamScores)
				{
					currentState = FSM_States::StandAndBoo;
					enemyTeamScores = false;
					startTime = std::chrono::high_resolution_clock().now();
				}
				break;
		case FSM_States::StandAndBoo:
			std::cout << "StandAndBoo\n";
				if (hungry)
					currentState = FSM_States::FoodStall;

				if(std::chrono::high_resolution_clock().now() - startTime > std::chrono::seconds(5))
				{
					currentState = FSM_States::Watch;
				}
				break;
			case FSM_States::StandAndCheer:
				std::cout << "StandAndCheer\n";
				if (hungry)
					currentState = FSM_States::FoodStall;

				if (std::chrono::high_resolution_clock().now() - startTime > std::chrono::seconds(5))
				{
					currentState = FSM_States::Watch;
				}
				break;
			case FSM_States::FoodStall:
				std::cout << "FoodStall\n";
				if(gotFood)
					currentState = FSM_States::SitAndEat;
				break;
			case FSM_States::SitAndEat:
				std::cout << "SitAndEat\n";
				if (std::chrono::high_resolution_clock().now() - startTime > std::chrono::minutes(5))
				{
					currentState = FSM_States::Watch;
				}
				break;
		}

		/*

		Write your code here for the finite state machine example

		*/

		// Sleep the current thread for 1000 milliseconds. Can be repalce with seconds(1)
		sleep_for(milliseconds(1000));

		if (_kbhit())
		{
			char input_char = _getch();

			std::cout << input_char;

			// Check for ESC key. See table here http://www.asciitable.com/
			if (input_char == 27)
			{
				program_running = false;
			}
			if (input_char == 75 && !homeTeamScores)
			{
				homeTeamScores = true;
			}
			if (input_char == 76 && !enemyTeamScores)
			{
				enemyTeamScores = true;
			}
			if (input_char == 77 && !hungry)
			{
				hungry = true;
			}
			if (input_char == 78 && !gotFood)
			{
				gotFood = true;
			}
		}

	} while (program_running);

	std::cout << "Ending Finite State Machine" << std::endl;

	return 0;
}