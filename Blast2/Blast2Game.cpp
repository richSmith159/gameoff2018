#include "Blast2Game.h"

#include <Tempest\ScreenList.h>


Blast2Game::Blast2Game() {
	// empty
}


Blast2Game::~Blast2Game() {
	// empty
}


void Blast2Game::onInit() {
	// empty
}


void Blast2Game::addScreens() {
	m_gameScreen = std::make_unique<GameScreen>(&m_window);
	m_screenList->addScreen(m_gameScreen.get());
	m_screenList->setScreen(m_gameScreen->getIndex());
}


void Blast2Game::onExit() {
	// empty
}