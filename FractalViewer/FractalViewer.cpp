#include "FractalViewer.h"

#include <Tempest\ScreenList.h>


FractalViewer::FractalViewer() {
	// empty
}


FractalViewer::~FractalViewer() {
	// empty
}


void FractalViewer::onInit() {
	// empty
}


void FractalViewer::addScreens() {
	m_fractalScreen = std::make_unique<FractalScreen>(&m_window);
	m_screenList->addScreen(m_fractalScreen.get());
	m_screenList->setScreen(m_fractalScreen->getIndex());
}


void FractalViewer::onExit() {
	// empty
}