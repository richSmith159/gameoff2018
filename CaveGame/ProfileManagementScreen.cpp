#include "ProfileManagementScreen.h"
#include "GameState.h"
#include "CaveGameScreenIndices.h"
#include <iostream>
#include <Tempest\IMainGame.h>


ProfileManagementScreen::ProfileManagementScreen(Tempest::Window* window) {
	m_index = PROFILE_MANAGEMENT_SCREEN;
	m_window = window;
}


ProfileManagementScreen::~ProfileManagementScreen() {
	// empty
}

int ProfileManagementScreen::getNextIndex() const {
	return PROFILE_MANAGEMENT_SCREEN;
}

int ProfileManagementScreen::getPrevIndex() const {
	return NO_SCREEN;
}

void ProfileManagementScreen::build() {
	// empty
}

void ProfileManagementScreen::destroy() {
	// empty
}

void ProfileManagementScreen::onEntry() {
	// init camera
	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
	m_camera.setScale(1.0f);
	m_camera.setPosition(glm::vec2(0.0f, 0.0f));

	initUI();

	m_currentProfile.deserialize(GAMESTATE::SELECTED_PROFILE_NAME);
	
}

void ProfileManagementScreen::onExit() {
	m_gui.destroy();
}

void ProfileManagementScreen::update(float deltaTime) {
	m_camera.update();
	checkInput();
	m_gui.update();
}

void ProfileManagementScreen::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.05f, 0.05f, 0.05f, 0.0f);
	m_gui.draw();
}

void ProfileManagementScreen::initUI() {
	m_gui.init("GUI");

	m_gui.loadScheme("TaharezLook.scheme");
	m_gui.setFont("DejaVuSans-10");

	SDL_ShowCursor(1);

	CEGUI::WindowManager& winManager = CEGUI::WindowManager::getSingleton();

}

void ProfileManagementScreen::loadProfile(std::string profileName) {

}

void ProfileManagementScreen::checkInput() {
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