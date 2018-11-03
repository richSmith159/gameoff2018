#include "TempestErrors.h"

#include <cstdlib>
#include <iostream>
#include <SDL\SDL.h>

namespace Tempest {
	void fatalError(std::string errorMessage) {

		// display error string
		std::cout << errorMessage << std::endl;
		std::cout << "Press any key to end...";

		// wait for key input to escape application
		int temp;
		std::cin >> temp;
		SDL_Quit();
		exit(69);

	}
}
