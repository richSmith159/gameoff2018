#include "CaveGenerationScreen.h"

#include <Tempest\IMainGame.h>
#include <Tempest\ResourceManager.h>
#include <SDL\SDL.h>

CaveGenerationScreen::CaveGenerationScreen(Tempest::Window* window) {
	m_window = window;
}


CaveGenerationScreen::~CaveGenerationScreen() {
	// empty
}

int CaveGenerationScreen::getNextIndex() const { return 0; }


int CaveGenerationScreen::getPrevIndex() const { return 0; }


void CaveGenerationScreen::build() {
	// empty
}


void CaveGenerationScreen::destroy() {
	// empty
}

void CaveGenerationScreen::onEntry() {

	// init camera
	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
	m_camera.setScale(4.0f);
	m_camera.setPosition(glm::vec2(0.0f, 0.0f));

	initUI();
}


void CaveGenerationScreen::onExit() {
	// empty
}

void CaveGenerationScreen::update(float deltaTime) {
	m_camera.update();
	checkInput();
}


void CaveGenerationScreen::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.05f, 0.05f, 0.05f, 0.0f);
}


void CaveGenerationScreen::initUI() {
	m_gui.init("GUI");
	SDL_ShowCursor(1);
}


void CaveGenerationScreen::checkInput() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		m_game->onSDLEvent(evnt);
		m_gui.onSDLEvent(evnt);
		switch (evnt.type) {
		case SDL_QUIT:
			exit(69);
			break;
		}
	}
}
