#include <iostream>		
#include <thread>	 
#include <chrono>
#include <conio.h>

using namespace std::this_thread;	// sleep_for
using namespace std::chrono;			// seconds, milliseconds

int main()
{
	bool program_running = true;

	std::cout << "Starting Finite State Machine. Press ESC key to close." << std::endl;

	do {

		/*

		Write your code here for the finite state machine example

		*/

		// Sleep the current thread for 1000 milliseconds. Can be repalce with seconds(1)
		sleep_for(milliseconds(1000));

		if (_kbhit())
		{
			char input_char = _getch();

			// Check for ESC key. See table here http://www.asciitable.com/
			if (input_char == 27)
			{
				program_running = false;
			}
		}

	} while (program_running);

	std::cout << "Ending Finite State Machine" << std::endl;

	return 0;
}