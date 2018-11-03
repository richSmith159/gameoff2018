#include "GameplayScreen.h"
#include "ScreenIndices.h"

#include <Tempest\IMainGame.h>
#include <Tempest\ResourceManager.h>

#include <SDL\SDL.h>
#include <string>
#include <iostream>


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
	m_camera.setScale(4.0f);
	m_camera.setPosition(glm::vec2(0.0f, 0.0f));
	initUI();
	m_entityRenderer.init();

	// load player texture
	Tempest::glTexture playerTexture = Tempest::ResourceManager::getTexture("Assets/Textures/Entities/player.png");

	m_player.init(
		5,
		0.5f,
		&m_game->inputManager,
		&m_camera,
		0,
		playerTexture
	);
	m_player.setPosition(glm::vec2(0.0f, 0.0f));

	m_squareSpawner.init(0.1f, 10.0f, 0.1f, &m_player);
}


void GameplayScreen::onExit() {
	// empty
}


void GameplayScreen::update(float deltaTime) {
	m_camera.update();
	m_squareSpawner.update();
	m_player.update(deltaTime);
	for (unsigned int i = 0; i < m_squareSpawner.m_entities.size(); i++) {
		m_squareSpawner.m_entities[i].update(deltaTime);
	}
	checkInput();
}


void GameplayScreen::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	m_entityRenderer.begin(&m_camera);
	for (unsigned int i = 0; i < m_squareSpawner.m_entities.size(); i++) {
		m_entityRenderer.render(&m_squareSpawner.m_entities[i]);
	}
	m_entityRenderer.render(&m_player);
	m_entityRenderer.end();
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
