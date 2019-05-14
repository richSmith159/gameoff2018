#include "FractalScreen.h"

#include <Tempest\IMainGame.h>
#include <Tempest\ResourceManager.h>

#include <SDL\SDL.h>
#include <string>
#include <iostream>
#include <glm\glm\gtx\rotate_vector.hpp>



FractalScreen::FractalScreen(Tempest::Window* window) { m_window = window; }


FractalScreen::~FractalScreen() {
	// empty
}


int FractalScreen::getNextIndex() const { return 0; }


int FractalScreen::getPrevIndex() const { return 0; }


void FractalScreen::build() {
	// empty
}


void FractalScreen::destroy() {
	// empty
}


void FractalScreen::onEntry() {

	// init camera
	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
	m_camera.setScale(4.0f);
	m_camera.setPosition(glm::vec2(0.0f, 0.0f));
	
	initUI();

	double screenWidth = (double)m_window->getScreenWidth();
	double screenHeight = (double)m_window->getScreenHeight();
	double initialZoom = 1.0;
	int initialIterations = 100;

	m_fractalRenderer.init();
	m_fractal.init(
		screenWidth,
		screenHeight,
		0.0,
		0.0,
		initialZoom,
		initialIterations
	);

}


void FractalScreen::onExit() {
}


void FractalScreen::update(float deltaTime) {
	m_timeCount += 0.01f;
	m_camera.update();
	checkInput();
	double spatialOffset = 0.01 / m_fractal.getZoom();
	double zoomOffset = 0.1;
	if (m_game->inputManager.isKeyDown(SDLK_UP)) {
		m_fractal.offsetZoom(zoomOffset);
	}
	if (m_game->inputManager.isKeyDown(SDLK_DOWN)) {
		m_fractal.offsetZoom(-zoomOffset);
	}
	if (m_game->inputManager.isKeyDown(SDLK_w)) {
		m_fractal.offsetCenterY(spatialOffset);
	}
	if (m_game->inputManager.isKeyDown(SDLK_s)) {
		m_fractal.offsetCenterY(-spatialOffset);
	}
	if (m_game->inputManager.isKeyDown(SDLK_a)) {
		m_fractal.offsetCenterX(-spatialOffset);
	}
	if (m_game->inputManager.isKeyDown(SDLK_d)) {
		m_fractal.offsetCenterX(spatialOffset);
	}
	if (m_game->inputManager.isKeyDown(SDLK_LEFT)) {
		m_fractal.offsetIterations(-1);
	}
	if (m_game->inputManager.isKeyDown(SDLK_RIGHT)) {
		m_fractal.offsetIterations(1);
	}
	if (m_game->inputManager.isKeyDown(SDLK_ESCAPE)) {
		exit(69);
	}
}


void FractalScreen::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.05f, 0.05f, 0.05f, 0.0f);
	m_fractalRenderer.begin(&m_camera);
	std::cout << m_fractal.getRGB().x << ", " << m_fractal.getRGB().y << ", " << m_fractal.getRGB().z << std::endl;
	m_fractalRenderer.render(&m_fractal);
	m_fractalRenderer.end();
}


void FractalScreen::initUI() {
	m_gui.init("GUI");
	SDL_ShowCursor(1);
}


void FractalScreen::checkInput() {
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
