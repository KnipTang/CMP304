#include <iostream>		
#include <thread>	 
#include <chrono>
#include <conio.h>
#include <map>

using namespace std::this_thread;	// sleep_for
using namespace std::chrono;			// seconds, milliseconds

using namespace std::chrono_literals;

auto startTime = std::chrono::high_resolution_clock().now();

bool enemyTeamScores = false;
bool homeTeamScores = false;

bool hungry = false;

bool gotFood = false;

class BaseState
{
	public: virtual BaseState* run() = 0;
};

void swapState(BaseState** current_state, BaseState* new_state);

class Watch : public BaseState
{
	BaseState* run() override
	{
		std::cout << "Watching\n";

		return nullptr;
	}
};

class StandAndBoo : public BaseState
{
	BaseState* run() override
	{
		std::cout << "StandAndBoo\n";

		return nullptr;
	}
};

class StandAndCheer : public BaseState
{
	BaseState* run() override
	{
		std::cout << "StandAndCheer\n";

		return nullptr;
	}
};

class FoodStall : public BaseState
{
	BaseState* run() override
	{
		std::cout << "FoodStall\n";

		return nullptr;
	}
};

class SitAndEat : public BaseState
{
	BaseState* run() override
	{
		std::cout << "SitAndEat\n";

		return nullptr;
	}
};

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
	Watch* watchState = new Watch{};
	StandAndBoo* booState = new StandAndBoo{};
	StandAndCheer* cheerState = new StandAndCheer{};
	FoodStall* foodStallState = new FoodStall{};
	SitAndEat* eatState = new SitAndEat{};

	BaseState* currentState = watchState;

	//std::map<BaseState*, BaseState*> currentStateMap;
	//
	//currentStateMap[new Watch] = watchState;
	//currentStateMap[new StandAndBoo] = booState;
	//currentStateMap[new StandAndCheer] = cheerState;
	//currentStateMap[new FoodStall] = foodStallState;
	//currentStateMap[new SitAndEat] = eatState;



	bool program_running = true;

	std::cout << "Starting Finite State Machine. Press ESC key to close." << std::endl;

	//FSM_States currentState = FSM_States::Watch;

	do {

		currentState->run();

		//BaseState* runReturn = currentStateMap.at(currentState)->run();
		//
		//if (runReturn != nullptr)
		//	currentState = runReturn;

		/*
		switch (currentState)
		{
			case FSM_States::Watch:
				std::cout << "Watching\n";

				if (hungry)
					swapState(&currentState, FSM_States::FoodStall);

				if (homeTeamScores)
				{
					swapState(&currentState, FSM_States::StandAndCheer);
					homeTeamScores = false;
					startTime = std::chrono::high_resolution_clock().now();
				}
				else if (enemyTeamScores)
				{
					swapState(&currentState, FSM_States::StandAndBoo);
					enemyTeamScores = false;
					startTime = std::chrono::high_resolution_clock().now();
				}
				break;
		case FSM_States::StandAndBoo:
			std::cout << "StandAndBoo\n";
				if (hungry)
					swapState(&currentState, FSM_States::FoodStall);

				if(std::chrono::high_resolution_clock().now() - startTime > std::chrono::seconds(5))
				{
					swapState(&currentState, FSM_States::Watch);
				}
				break;
			case FSM_States::StandAndCheer:
				std::cout << "StandAndCheer\n";
				if (hungry)
					swapState(&currentState, FSM_States::FoodStall);

				if (std::chrono::high_resolution_clock().now() - startTime > std::chrono::seconds(5))
				{
					swapState(&currentState, FSM_States::Watch);
				}
				break;
			case FSM_States::FoodStall:
				std::cout << "FoodStall\n";
				if(gotFood)
					swapState(&currentState, FSM_States::SitAndEat);
				break;
			case FSM_States::SitAndEat:
				std::cout << "SitAndEat\n";
				if (std::chrono::high_resolution_clock().now() - startTime > std::chrono::minutes(5))
				{
					swapState(&currentState, FSM_States::Watch);
				}
				break;
		}
		*/
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
			if (input_char == 75 && currentState == watchState)
			{
				//homeTeamScores = true;
				swapState(&currentState, cheerState);
			}
			if (input_char == 76 && !enemyTeamScores && currentState == watchState)
			{
				//enemyTeamScores = true;

				swapState(&currentState, booState);
			}
			if (input_char == 77 && !hungry && currentState != eatState)
			{
				//hungry = true;

				swapState(&currentState,foodStallState);
			}
			if (input_char == 78 && !gotFood && currentState == foodStallState)
			{
				//gotFood = true;

				swapState(&currentState,eatState);
			}
		}

	} while (program_running);

	std::cout << "Ending Finite State Machine" << std::endl;

	return 0;
}

void swapState(BaseState** current_state, BaseState* new_state)
{
	*current_state = new_state;
}