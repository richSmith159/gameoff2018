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

	// init camera
	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
	m_camera.setScale(4.0f);
	m_camera.setPosition(glm::vec2(0.0f, 0.0f));

	initUI();

	// init the physics system with no gravity
	// there is no 'down' in this game
	m_physicsSystem.initSystem(0.0f, 0.0f);

	// set to default renderer and init sprite system
	m_spriteSystem.setRenderer(&m_defaultRenderer);
	m_spriteSystem.initSystem(&m_camera);

	spawnEnemy("Assets/Textures/Entities/square.png", glm::vec2(0.0f), 16.0f, 16.0f);
	std::cout << "AFTER ADD: " << m_entityManager.getEntity(0)->m_physicsComponent->lol << std::endl;
}


void GameScreen::onExit() {
}


void GameScreen::update(float deltaTime) {
	std::cout << "Update" << std::endl;
	m_physicsSystem.run(deltaTime);
	checkInput();
}


void GameScreen::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	std::cout << "Draw" << std::endl;
	// pass in deltaTime = 0.0f for sprite system as not needed
	m_spriteSystem.run(0.0f);
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

void GameScreen::spawnEnemy(const std::string & spriteTexturePath, glm::vec2 initialPosition, const float& width, const float& height) {
	Tempest::glTexture spriteTexture = Tempest::ResourceManager::getTexture(spriteTexturePath);
	PhysicsComponent* enemyPhysics = m_physicsSystem.addComponent(b2_dynamicBody, initialPosition.x, initialPosition.y, 0.0f);
	SpriteComponent* enemySprite = m_spriteSystem.addComponent(spriteTexture, Tempest::ColorRGBA8(255, 255, 255, 255), width, height);
	m_entityManager.addEntity(nullptr, enemyPhysics, enemySprite);
}
