#include "IMainGame.h"
#include "FPSLimiter.h"
#include "IGameScreen.h"
#include "ScreenList.h"

#include <GL\glew.h>
#include <iostream>

namespace Tempest {

	IMainGame::IMainGame() {
		// init the screen list
		m_screenList = std::make_unique<ScreenList>(this);
	}


	IMainGame::~IMainGame() {
		// empty
	}

	bool IMainGame::initSystems() {

		// create the game window and initialize openGL
		m_window.create(m_appName, m_screenWidth, m_screenHeight);
		return true;

	}

	bool IMainGame::initGame() {

		// check systems initialization was successfull
		if (!initSystems()) {
			return false;
		}

		// call custom initialization logic
		onInit();

		// add screens to game
		addScreens();

		// get current screen and run any logic for scene init using onEntry()
		m_currentScreen = m_screenList->getCurrentScreen();
		m_currentScreen->onEntry();
		m_currentScreen->setRunning();

		return true;

	}


	void IMainGame::update(float deltaTime) {

		// if there is a current screen update depending on state
		if (m_currentScreen) {
			switch (m_currentScreen->getState()) {
			case ScreenState::RUNNING:
				m_currentScreen->update(deltaTime);
				break;
			case ScreenState::CHANGE_NEXT:
				m_currentScreen->onExit();
				m_currentScreen = m_screenList->moveToNext();
				if (m_currentScreen) {
					m_currentScreen->setRunning();
					m_currentScreen->onEntry();
				}
				break;
			case ScreenState::CHANGE_PREV:
				m_currentScreen->onExit();
				m_currentScreen = m_screenList->moveToPrevious();
				if (m_currentScreen) {
					m_currentScreen->setRunning();
					m_currentScreen->onEntry();
				}
				break;
			case ScreenState::EXIT:
				exitGame();
				break;
			default:
				break;

			}
		}
		else {
			exitGame();
		}
	}

	void IMainGame::draw() {
		// set the opengl viewport
		glViewport(0, 0, m_window.getScreenWidth(), m_window.getScreenHeight());

		// draw the screen if there is a screen and it's state is running
		if (m_currentScreen && m_currentScreen->getState() == ScreenState::RUNNING) {
			m_currentScreen->draw();
		}
	}

	void IMainGame::runGame() {

		// call and check the status of the init game function
		if (!initGame()) {
			return;
		}

		// SET FPS LIMITER
		FPSLimiter fpsLimiter;
		fpsLimiter.setMaxFPS(60.0f);

		// define quantities to avoid using arbitrary numbers in code
		const float MS_PER_SEC = 1000.0f;
		const float IDEAL_FPS = 60.0f;

		// const to limit the number of steps in the semi-fixed timestep
		// avoids spiral of death
		// (never reach drawing stage due to too many timestep checks)
		const int MAX_TS_STEPS = 6;


		// deal number of milliseconds to complete one frame
		const float IDEAL_FRAME_TIME = MS_PER_SEC / IDEAL_FPS;

		// should never be higher than 1
		const float MAX_DELTATIME = 1.0f;

		// get number of milliseconds since SDL was initialized
		float previousTicks = SDL_GetTicks();

		// set the running bool and run the game loop
		m_isRunning = true;

		while (m_isRunning) {

			// get the ticks
			fpsLimiter.beginFrame();
			// keep track of ticks in both previous and current frames
			float newTicks = SDL_GetTicks();

			// frame time inversely proportional to FPS
			float frameTime = newTicks - previousTicks;
			previousTicks = newTicks;


			float calculatedDeltaTime = frameTime / IDEAL_FRAME_TIME;


			// update input manager to get any changes in input
			inputManager.update();

			// update and draw the game
			update(calculatedDeltaTime);
			draw();

			// get the fps from the calculations
			m_fps = fpsLimiter.end();
			// swap the buffers
			m_window.swapBuffers();
		}
	}

	void IMainGame::exitGame() {

		// call current screen's exit code
		m_currentScreen->onExit();

		if (m_screenList) {

			// destroy screens and free memory
			m_screenList->destroy();
			m_screenList.reset();

		}

		// set running bool to false to exit game loop
		m_isRunning = false;

	}


	void IMainGame::onInit() {
		// empty
	}

	// set up all screens for main game
	void IMainGame::addScreens() {
		// empty
	}

	// clean up when exiting game
	void IMainGame::onExit() {
		// empty
	}

	void IMainGame::onSDLEvent(SDL_Event& evnt) {

		// update input manager with sdl events
		switch (evnt.type) {
		case SDL_QUIT:
			exitGame();
			break;
		case SDL_MOUSEMOTION:
			inputManager.setMouseCoords((float)evnt.motion.x, (float)evnt.motion.y);
			break;
		case SDL_KEYDOWN:
			inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			inputManager.releaseKey(evnt.button.button);
			break;

		}
	}
}