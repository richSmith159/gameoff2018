#include "Window.h"
#include "TempestErrors.h"
#include <iostream>
#include <GL/glew.h>


namespace Tempest {

	Window::Window() {
		// empty
	}

	Window::~Window() {
		// empty
	}

	int Window::create(std::string windowName, int screenWidth, int screenHeight) {

		// set the dimensions
		m_width = screenWidth;
		m_height = screenHeight;

		// create the SDL window
		m_window = SDL_CreateWindow(
			windowName.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			m_width,
			m_height,
			SDL_WINDOW_OPENGL);

		// check window creation was successfull
		if (m_window == nullptr) {
			fatalError("SDL window could not be created! Exiting.");
		}

		SDL_DisplayMode desktopDisplay;
		if (SDL_GetDesktopDisplayMode(0, &desktopDisplay) != 0) {
			SDL_Log("Could not get screen resolution. Using default. ERROR: %s", SDL_GetError());
		}
		else {
			std::cout << "screen resolution: " << desktopDisplay.w << ", " << desktopDisplay.w << std::endl;
			SDL_MaximizeWindow(m_window);
			m_width = desktopDisplay.w;
			m_height = desktopDisplay.h;
			SDL_SetWindowSize(m_window, desktopDisplay.w, desktopDisplay.h);
		}

		// create opengl context and pass to window
		SDL_GLContext glContext = SDL_GL_CreateContext(m_window);

		// check context creation was successfull
		if (glContext == nullptr) {
			fatalError("OpenGL context could not be created! Exiting.");
		}

		// init GLEW
		GLenum glewInitResult = glewInit();

		// check glew init result for success or failure
		if (glewInitResult != GLEW_OK) {
			fatalError("GLEW could not be initialized! Exiting.");
		}

		// display opengl version in the console
		std::printf("****    OpenGL Version: %s    ****\n", glGetString(GL_VERSION));

		// set the window's background color
		glClearColor(0.1f, 0.17f, 0.17f, 1.0f);

		// set VSYNC on
		// SDL_GL_SetSwapInterval(0);

		// enable alpha blending
		glEnable(GL_ALPHA_TEST);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}

}
