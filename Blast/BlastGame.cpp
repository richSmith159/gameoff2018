#include "BlastGame.h"

#include <Tempest\ScreenList.h>


BlastGame::BlastGame() {
	// empty
}


BlastGame::~BlastGame() {
	// empty
}


void BlastGame::onInit() {
	// empty
}


void BlastGame::addScreens() {
	m_gameplayScreen = std::make_unique<GameplayScreen>(&m_window);
	m_screenList->addScreen(m_gameplayScreen.get());
	m_screenList->setScreen(m_gameplayScreen->getIndex());
}


void BlastGame::onExit() {
	// empty
}