#pragma once

#define NO_SCREEN_INDEX -1

namespace Tempest {

	class IMainGame;

	enum class ScreenState {
		NONE,
		RUNNING,
		EXIT,
		CHANGE_NEXT,
		CHANGE_PREV
	};

	class IGameScreen
	{
	public:

		friend class ScreenList;

		IGameScreen();
		virtual ~IGameScreen();

		// get next/previous screen index
		virtual int getNextIndex() const = 0;
		virtual int getPrevIndex() const = 0;

		// call at start of application
		virtual void build() = 0;

		// call at end of application
		virtual void destroy() = 0;

		// call when entering screen to perfrom initialization
		virtual void onEntry() = 0;

		// call when exiting a screen to perform clean up
		virtual void onExit() = 0;

		// call in main loop
		virtual void update(float deltaTime) = 0;
		virtual void draw() = 0;

		// gets current screen index
		int getIndex() {
			return m_index;
		}

		// set the screen's parent game
		void setGame(IMainGame* mainGame) {
			m_game = mainGame;
		}

		void setRunning() {
			m_currentState = ScreenState::RUNNING;
		}

		ScreenState getState() const { return m_currentState; }

	protected:

		// initial index of screen
		int m_index = -1;

		// default screenstate = NONE
		ScreenState m_currentState = ScreenState::NONE;

		// pointer to game screen belongs to
		// (set to nullptr for easier debugging)
		IMainGame* m_game = nullptr;

	};

}


