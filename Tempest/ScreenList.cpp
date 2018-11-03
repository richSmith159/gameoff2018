#include "ScreenList.h"
#include "IGameScreen.h"

namespace Tempest {

	ScreenList::ScreenList(IMainGame* mainGame) : m_game(mainGame) {
		// empty
	}

	ScreenList::~ScreenList() { destroy(); }

	IGameScreen* ScreenList::moveToNext() {
		IGameScreen* currentScreen = getCurrentScreen();

		// only move to next screen if it exists
		if (currentScreen->getNextIndex() != NO_SCREEN_INDEX) {
			m_currentIndex = currentScreen->getNextIndex();
		}

		// return next screen if it exists
		// if it does not exist, function will return 
		return getCurrentScreen();
	}

	IGameScreen* ScreenList::moveToPrevious() {
		IGameScreen* currentScreen = getCurrentScreen();

		// only move to next screen if it exists
		if (currentScreen->getPrevIndex() != NO_SCREEN_INDEX) {
			m_currentIndex = currentScreen->getPrevIndex();
		}

		// return next screen if it exists
		// if it does not exist, function will return 
		return getCurrentScreen();
	}


	void ScreenList::setScreen(int newSceneIndex) {
		m_currentIndex = newSceneIndex;
	}


	void ScreenList::addScreen(IGameScreen* newScreen) {

		// set index of new screen and add to the screenlist
		newScreen->m_index = m_screens.size();
		m_screens.push_back(newScreen);

		// call new screen's build function
		// (runs any screen specific build code)
		newScreen->build();

		// set the screen's game
		newScreen->setGame(m_game);

	}

	void ScreenList::destroy() {

		// iterate over and destory all contained screens
		for (size_t i = 0; i < m_screens.size(); i++) {
			m_screens[i]->destroy();
		}

		// resizing to 0 => if destroy called twice...
		// above loop will not cause errors
		m_screens.resize(0);
		m_currentIndex = NO_SCREEN_INDEX;
	}

	IGameScreen* ScreenList::getCurrentScreen() {

		// return null pointer if no screen at current index
		if (m_currentIndex == NO_SCREEN_INDEX) {
			return nullptr;
		}

		// if screen present at current index, return it
		return m_screens[m_currentIndex];
	}

}