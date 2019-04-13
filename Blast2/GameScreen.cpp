#include "GameScreen.h"
#include "Screens.h"

#include <Tempest\IMainGame.h>
#include <Tempest\ResourceManager.h>

#include <SDL\SDL.h>
#include <string>
#include <iostream>
#include <glm\glm\gtx\rotate_vector.hpp>


GameScreen::GameScreen(Tempest::Window* window) { m_window = window; }


GameScreen::~GameScreen() {
	// empty
}


int GameScreen::getNextIndex() const { return NO_SCREEN; }


int GameScreen::getPrevIndex() const { return NO_SCREEN; }


void GameScreen::build() {
	// empty
}


void GameScreen::destroy() {
	// empty
}


void GameScreen::onEntry() {
	std::cout << "On Entry" << std::endl;
	m_spriteSystem.initSystem(&m_camera);
	initUI();
}


void GameScreen::onExit() {
}


void GameScreen::update(float deltaTime) {
	std::cout << "Update" << std::endl;
	checkInput();
}


void GameScreen::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	std::cout << "Draw" << std::endl;
}


void GameScreen::initUI() {
	m_gui.init("GUI");
	SDL_ShowCursor(1);
	std::cout << "Init UI" << std::endl;
}


void GameScreen::checkInput() {
	std::cout << "Check Input" << std::endl;
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
