#include "CaveGame.h"

#include <Tempest\ScreenList.h>

CaveGame::CaveGame() {
	// empty
}


CaveGame::~CaveGame() {
	// empty
}

void CaveGame::onInit() {
	// empty
}

void CaveGame::addScreens() {
	m_mainMenuScreen = std::make_unique<MainMenuScreen>(&m_window);
	m_caveGenerationScreen = std::make_unique<CaveGenerationScreen>(&m_window);
	m_profileManagementScreen = std::make_unique<ProfileManagementScreen>(&m_window);

	m_screenList->addScreen(m_mainMenuScreen.get());
	m_screenList->addScreen(m_caveGenerationScreen.get());
	m_screenList->addScreen(m_profileManagementScreen.get());
	m_screenList->setScreen(m_mainMenuScreen->getIndex());
}

void CaveGame::onExit() {
	// empty
}