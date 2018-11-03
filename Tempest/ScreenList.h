#pragma once

#include <vector>

namespace Tempest {

	class IMainGame;
	class IGameScreen;

	class ScreenList {

	public:

		ScreenList(IMainGame* mainGame);
		~ScreenList();

		// move to next/previous screen in vector
		IGameScreen* moveToNext();
		IGameScreen* moveToPrevious();

		// set current screen
		void setScreen(int newSceneIndex);

		// add screen to vector
		void addScreen(IGameScreen* newScreen);

		// iterate over screens and destroy them
		// also resizes vector to 0 and sets current index to NO_SCREEN_INDEX
		void destroy();

		// function to get pointer to current screen
		// returns nullptr if no current index
		IGameScreen* getCurrentScreen();

	protected:
		// vector of all screens
		std::vector<IGameScreen*> m_screens;

		// current screen index
		int m_currentIndex = -1;

		// pointer to main game
		IMainGame* m_game = nullptr;
	};

}
