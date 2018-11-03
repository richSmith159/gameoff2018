#pragma once


#include <memory>
#include <SDL/SDL.h>
#include "Window.h"
#include "InputManager.h"

namespace Tempest {

	class ScreenList;
	class IGameScreen;

	class IMainGame
	{
	public:
		IMainGame();
		~IMainGame();

		// runs game and starts game loops
		void runGame();

		// exits the game and calls clean-up functions
		void exitGame();

		// virtual function to hold game-specific initialization logic
		virtual void onInit() = 0;

		// setup screens for main game
		virtual void addScreens() = 0;

		// function to hold game-specific logic when exiting the game
		virtual void onExit() = 0;

		// get the game's FPS
		const float getFPS() const { return m_fps; }

		void onSDLEvent(SDL_Event& evnt);

		InputManager inputManager;

		// string to be used as a buffer to pass data between screens
		std::string m_buffer;

		// used if a bool needed passing between screens
		bool m_boolBuffer;

		void setAppName(const std::string& name) { m_appName = name; }
		void setInitialScreenWidth(const int& width) { m_screenWidth = width; }
		void setInitialScreenHeight(const int& height) { m_screenHeight = height; }
		
	protected:

		// functions only needed by the game
		void update(float deltaTime);

		void draw();

		// functions to initialize the game
		bool initGame();
		bool initSystems();

		// current fps
		float m_fps = 0;

		// smart pointer to list of game screens
		std::unique_ptr<ScreenList> m_screenList = nullptr;

		// currently running screen
		IGameScreen* m_currentScreen = nullptr;

		// is the game running
		bool m_isRunning = false;

		// window to display game in
		Window m_window;

		// initial values for game window display
		int m_screenWidth = 800;
		int m_screenHeight = 600;
		std::string m_appName = "default";

	};

}