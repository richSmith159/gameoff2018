#pragma once
#include <CEGUI\CEGUI.h>
#include <CEGUI\RendererModules\OpenGL\GL3Renderer.h>
#include <glm\glm\glm.hpp>
#include <SDL\SDL_events.h>

namespace Tempest {

	class GUI
	{
	public:

		GUI();
		~GUI();

		// inits the renderer and sets up resource directory based on function input
		// also creates the context and the root window
		void init(const std::string& resourceDirectory);
		void destroy();
		void update();
		void draw();

		void loadScheme(const std::string& schemeFile);
		void setFont(const std::string& fontFile);

		// basic input injection
		// takes SDL_EVENT, converts it to a CEGUI event then injects it into the GUI
		void onSDLEvent(SDL_Event& evnt);

		// functions for displaying/hiding cursor
		void showMouseCursor() { m_context->getMouseCursor().show(); }
		void hideMouseCursor() { m_context->getMouseCursor().hide(); }

		// set the cursor image
		void setMouseCursor(const std::string& imageFile) { m_context->getMouseCursor().setDefaultImage(imageFile); }

		// creates CEGUI widget with no parent (widgets are a type of CEGUI window)
		// widget size can be defined in terms of percentage or pixels
		CEGUI::Window* createWidget(
			const std::string& type,
			const glm::vec4& destRectPercentage,
			const glm::vec4& destRectPixel,
			const std::string& name = ""
		);

		// creates CEGUI widget with a parent (widgets are a type of CEGUI window)
		// widget size/location can be defined in terms of percentage or pixels
		CEGUI::Window* createWidget(
			CEGUI::Window* parent,
			const std::string& type,
			const glm::vec4& destRectPercentage,
			const glm::vec4& destRectPixel,
			const std::string& name = ""
		);

		// sets the size and location of a widget in terms of percentage or pixels
		static void setWidgetDestRect(
			CEGUI::Window* widget,
			const glm::vec4& destRectPercentage,
			const glm::vec4& destRectPixel
		);

		// getters
		static CEGUI::OpenGL3Renderer* getRenderer() { return m_renderer; }
		const CEGUI::GUIContext* getContext() { return m_context; }
	
	private:

		// gui renderer
		static CEGUI::OpenGL3Renderer* m_renderer;

		// context to draw the GUI with
		CEGUI::GUIContext* m_context = nullptr;

		// root window to which all widgets get parented to
		CEGUI::Window* m_root = nullptr;

		// keeps track of time
		unsigned int m_lastTime = 0;

	};

}
