#include "CaveGenerationScreen.h"

#include <Tempest\IMainGame.h>
#include <Tempest\ResourceManager.h>
#include <SDL\SDL.h>

#include <iostream>

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

	m_caveMap.init(10, 10, 45);
	m_renderer.init();
	Cell* firstCell = m_caveMap.getCell(0, 0);
	for (int i = 0; i < 25; i ++) {
		Cell* cell = m_caveMap.getCell(i);
		std::cout << cell->position.x << ", " << cell->position.y << std::endl;

	}
}


void CaveGenerationScreen::onExit() {
	// empty
}

void CaveGenerationScreen::update(float deltaTime) {
	m_camera.update();
	checkInput();
	if (m_game->inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
		glm::vec2 coords = m_game->inputManager.getMouseCoords();
		std::cout << "mouse: " << coords.x << ", " << coords.y << std::endl;
	}
	if (m_game->inputManager.isKeyDown(SDLK_w)) {
		m_camera.offsetPosition(glm::vec2(0.0f, 3.0f));
	}
	if (m_game->inputManager.isKeyDown(SDLK_s)) {
		m_camera.offsetPosition(glm::vec2(0.0f, -3.0f));
	}
	if (m_game->inputManager.isKeyDown(SDLK_a)) {
		m_camera.offsetPosition(glm::vec2(-3.0f, 0.0f));
	}
	if (m_game->inputManager.isKeyDown(SDLK_d)) {
		m_camera.offsetPosition(glm::vec2(3.0f, 0.0f));
	}
	if (m_game->inputManager.isKeyDown(SDLK_ESCAPE)) {
		exit(69);
	}
	// std::cout << "FPS: " << m_game->getFPS() << std::endl;
}


void CaveGenerationScreen::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.05f, 0.05f, 0.05f, 0.0f);
	m_renderer.begin(&m_camera);
	static const glm::vec4 simpleUV = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	for (int i = 0; i < m_caveMap.getTotalCells(); i++) {
		Cell* currentCell = m_caveMap.getCell(i);
		m_renderer.render(
			currentCell->calculateDestRect(),
			simpleUV,
			currentCell->texture.id,
			1,
			currentCell->color,
			0.0f
		);
	}

	m_renderer.end();
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
