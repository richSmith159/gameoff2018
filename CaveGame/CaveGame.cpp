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
	m_caveGenerationScreen = std::make_unique<CaveGenerationScreen>(&m_window);
	m_screenList->addScreen(m_caveGenerationScreen.get());
	m_screenList->setScreen(m_caveGenerationScreen->getIndex());
}

void CaveGame::onExit() {
	// empty
}