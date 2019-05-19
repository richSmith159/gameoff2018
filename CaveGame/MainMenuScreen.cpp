#include "MainMenuScreen.h"
#include <Tempest\IMainGame.h>
#include "CaveGameScreenIndices.h"
#include "PlayerProfile.h"


MainMenuScreen::MainMenuScreen(Tempest::Window* window) {
	m_window = window;
}


MainMenuScreen::~MainMenuScreen() {
	// empty
}

int MainMenuScreen::getNextIndex() const {
	return PROFILE_MANAGEMENT_SCREEN;
}

int MainMenuScreen::getPrevIndex() const{
	return NO_SCREEN;
}

void MainMenuScreen::build() {
	// empty
}

void MainMenuScreen::destroy() {
	// empty
}

void MainMenuScreen::onEntry() {
	// init camera
	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
	m_camera.setScale(1.0f);
	m_camera.setPosition(glm::vec2(0.0f, 0.0f));

	initUI();
}

void MainMenuScreen::onExit() {
	m_gui.destroy();
}

void MainMenuScreen::update(float deltaTime) {
	m_camera.update();
	checkInput();
	m_gui.update();
}

void MainMenuScreen::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.05f, 0.05f, 0.05f, 0.0f);
	m_gui.draw();
}

void MainMenuScreen::initUI() {
	m_gui.init("GUI");

	m_gui.loadScheme("TaharezLook.scheme");
	m_gui.setFont("DejaVuSans-10");

	SDL_ShowCursor(1);

	CEGUI::WindowManager& winManager = CEGUI::WindowManager::getSingleton();


	// SET UP INITIAL MENU
	{
		m_initialGroupBox = static_cast<CEGUI::GroupBox*>(
			m_gui.createWidget(
				"TaharezLook/GroupBox",
				glm::vec4(0.25f, 0.20f, 0.50f, 0.36f),
				glm::vec4(0.0f),
				"InitialGroupBox"
			)
		);

		m_newProfileButton = static_cast<CEGUI::PushButton*>(
			m_gui.createWidget("TaharezLook/Button",
				glm::vec4(0.45f, 0.30f, 0.1f, 0.035f),
				glm::vec4(0.0f),
				"New Profile"
			)
		);
		
		m_loadProfileButton = static_cast<CEGUI::PushButton*>(
			m_gui.createWidget("TaharezLook/Button",
				glm::vec4(0.45f, 0.35f, 0.1f, 0.035f),
				glm::vec4(0.0f),
				"Load Profile"
			)
		);

		m_exitButton = static_cast<CEGUI::PushButton*>(
			m_gui.createWidget("TaharezLook/Button",
				glm::vec4(0.45f, 0.40f, 0.1f, 0.035f),
				glm::vec4(0.0f),
				"TestButton"
			)
		);

		m_newProfileButton->setText("New Profile");
		m_loadProfileButton->setText("Load Profile");
		m_exitButton->setText("Exit Game");

		m_initialGroupBox->setText("Main Menu");
		m_initialGroupBox->setAlwaysOnTop(false);
		m_initialGroupBox->moveToBack();
		m_initialGroupBox->disable();

		m_exitButton->subscribeEvent(
			CEGUI::RadioButton::EventMouseClick,
			CEGUI::Event::Subscriber(&MainMenuScreen::onExitClicked, this)
		);

		m_newProfileButton->subscribeEvent(
			CEGUI::RadioButton::EventMouseClick,
			CEGUI::Event::Subscriber(&MainMenuScreen::onNewProfileClicked, this)
		);
	}

	// SET UP NEW PROFILE MENU
	{
		m_newProfileGroupBox = static_cast<CEGUI::GroupBox*>(
			m_gui.createWidget(
				"TaharezLook/GroupBox",
				glm::vec4(0.25f, 0.20f, 0.50f, 0.36f),
				glm::vec4(0.0f),
				"NewProfileGroupBox"
			)
		);

		CEGUI::WindowManager& winManager = CEGUI::WindowManager::getSingleton();
		// m_newProfileLabel = winManager.createWindow("TaharezLook/Label", "");

		m_newProfileLabel = static_cast<CEGUI::Window*>(
			m_gui.createWidget(
				"TaharezLook/Label",
				glm::vec4(0.30f, 0.30f, 0.075f, 0.035f),
				glm::vec4(0.0f),
				"NewProfileNameLabel"
			)
		);

		m_nameInput = static_cast<CEGUI::Editbox*>(
			m_gui.createWidget(
				"TaharezLook/Editbox",
				glm::vec4(0.50f, 0.30f, 0.15f, 0.035f),
				glm::vec4(0.0f),
				"NewProfileNameInput"
			)
		);

		m_createProfileButton = static_cast<CEGUI::PushButton*>(
			m_gui.createWidget("TaharezLook/Button",
				glm::vec4(0.45f, 0.40f, 0.1f, 0.035f),
				glm::vec4(0.0f),
				"CreateProfileButton"
			)
		);

		m_cancelNewProfile = static_cast<CEGUI::PushButton*>(
			m_gui.createWidget("TaharezLook/Button",
				glm::vec4(0.45f, 0.5f, 0.1f, 0.035f),
				glm::vec4(0.0f),
				"CancelProfileButton"
			)
		);

		m_cancelNewProfile->subscribeEvent(
			CEGUI::RadioButton::EventMouseClick,
			CEGUI::Event::Subscriber(&MainMenuScreen::onCancelNewProfileClicked, this)
		);

		m_newProfileLabel->setText("Profile Name");
		m_newProfileGroupBox->setText("New Profile");
		m_createProfileButton->setText("Confirm");
		m_cancelNewProfile->setText("Cancel");
	}
	setNewProfileMenuVisibility(false);
}

void MainMenuScreen::setInitialMenuVisibility(bool visible) {
	m_initialGroupBox->setVisible(visible);
	m_newProfileButton->setVisible(visible);
	m_loadProfileButton->setVisible(visible);
	m_exitButton->setVisible(visible);
}

void MainMenuScreen::setNewProfileMenuVisibility(bool visible) {
	m_newProfileGroupBox->setVisible(visible);
	m_newProfileLabel->setVisible(visible);
	m_nameInput->setVisible(visible);
	m_createProfileButton->setVisible(visible);
	m_cancelNewProfile->setVisible(visible);
}

bool MainMenuScreen::onExitClicked(const CEGUI::EventArgs& e) {
	m_currentState = Tempest::ScreenState::EXIT;
	return true;
}

bool MainMenuScreen::onNewProfileClicked(const CEGUI::EventArgs & e) {
	setInitialMenuVisibility(false);
	setNewProfileMenuVisibility(true);
	return true;
}

bool MainMenuScreen::onCancelNewProfileClicked(const CEGUI::EventArgs & e) {
	setInitialMenuVisibility(true);
	setNewProfileMenuVisibility(false);
	return true;
}

bool MainMenuScreen::onConfirmNewProfileClicked(const CEGUI::EventArgs & e) {
	PlayerProfile newProfile;
	newProfile.init(m_nameInput->getText().c_str(), 200);
	newProfile.serialize();
	return true;
}

void MainMenuScreen::checkInput() {
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