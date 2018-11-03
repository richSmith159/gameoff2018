#pragma once

#include <string>
#include <SDL\SDL.h>

namespace Tempest {
	
	class Window
	{
	public:
		Window();
		~Window();

		// create window and set opengl properties
		int create(std::string windowName, int screenWidth, int screenHeight);

		// wrapper function for swapping buffers
		void swapBuffers() { SDL_GL_SwapWindow(m_window); }

		// set screen dimensions
		void setScreenWidth(const int& newWidth) { m_width = newWidth; }
		void setScreenHeight(const int& newHeight) { m_height = newHeight; }

		// get screen dimensions
		int getScreenWidth() { return m_width; }
		int getScreenHeight() { return m_height; }

		// get handle to SDL window
		SDL_Window* getSDLWindowHandle() { return m_window; }

	private:

		// screen dimensions
		int m_width;
		int m_height;

		// pointer to SDL window instance
		SDL_Window* m_window;

	};

}