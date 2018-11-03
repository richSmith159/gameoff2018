#include "GameplayScreen.h"
#include "ScreenIndices.h"

#include <Tempest\IMainGame.h>

#include <SDL\SDL.h>


GameplayScreen::GameplayScreen(Tempest::Window* window) { m_window = window; }


GameplayScreen::~GameplayScreen() {
	// empty
}


int GameplayScreen::getNextIndex() const { return NO_SCREEN; }


int GameplayScreen::getPrevIndex() const { return NO_SCREEN; }


void GameplayScreen::build() {
	// empty
}


void GameplayScreen::destroy() {
	// empty
}


void GameplayScreen::onEntry() {
	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
	m_camera.setScale(32.0f);
	initUI();
}


void GameplayScreen::onExit() {
	// empty
}


void GameplayScreen::update(float deltaTime) {
	m_camera.update();
	checkInput();
}


void GameplayScreen::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5, 0.5, 0.8, 1);
}


void GameplayScreen::initUI() {
	m_gui.init("GUI");
	SDL_ShowCursor(1);
}


void GameplayScreen::checkInput() {

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
