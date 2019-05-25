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

	m_caveMap.init(60, 60, 47);
	m_renderer.init();
	Tempest::glTexture minerTexture = Tempest::ResourceManager::getTexture("Textures/player.png");
	
	m_testMiner.init("test", 100, 3.0f, glm::vec2(1.0f), glm::vec2(1.0f, 0.0f), minerTexture);
	glClearColor(0.25f, 0.25f, 0.25f, 0.0f);
}


void CaveGenerationScreen::onExit() {
	m_gui.destroy();
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
	if (m_game->inputManager.isKeyDown(SDLK_e)) {
		m_camera.offsetScale(0.05f);
	}
	if (m_game->inputManager.isKeyDown(SDLK_q)) {
		m_camera.offsetScale(-0.05f);
	}
	//std::cout << "FPS: " << m_game->getFPS() << std::endl;
	m_gui.update();
}


void CaveGenerationScreen::draw() {
	static const glm::vec4 SIMPLE_UV = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// glClearDepth(1.0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_renderer.begin(&m_camera);
	m_renderer.beginTileSpriteBatch();
	for (int i = 0; i < m_caveMap.getTotalCells(); i++) {
		Cell* currentCell = m_caveMap.getCell(i);
		if (m_camera.isBoundingBoxInCameraView(currentCell->position, glm::vec2(CELL_WIDTH))) {
			m_renderer.renderTile(
				currentCell->calculateDestRect(),
				SIMPLE_UV,
				currentCell->texture.id,
				0.0f,
				currentCell->color,
				0.0f
			);
		}
	}
	m_renderer.endTileSpriteBatch();
	m_renderer.beginCharacterSpriteBatch();
	m_renderer.renderCharacter(
		m_testMiner.calculateDestRect(),
		SIMPLE_UV,
		m_testMiner.getTexture().id,
		0.0f,
		Tempest::ColorRGBA8(255, 255, 255, 255),
		m_testMiner.getDirection()
	);
	m_renderer.endCharacterSpriteBatch();
	m_renderer.end();
	m_gui.draw();
}


void CaveGenerationScreen::initUI() {
	m_gui.init("GUI");
	SDL_ShowCursor(1);

	m_gui.loadScheme("TaharezLook.scheme");
	m_gui.setFont("DejaVuSans-10");

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
