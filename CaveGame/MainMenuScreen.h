#pragma once

#include <Tempest\Window.h>
#include <Tempest\IGameScreen.h>
#include <Tempest\GUI.h>
#include <Tempest\Camera2D.h>


class MainMenuScreen : public Tempest::IGameScreen
{
public:
	MainMenuScreen(Tempest::Window* window);
	~MainMenuScreen();
	virtual int getNextIndex() const override;
	virtual int getPrevIndex() const override;
	virtual void build() override;
	virtual void destroy() override;
	virtual void onEntry() override;
	virtual void onExit() override;
	virtual void update(float deltaTime) override;
	virtual void draw() override;

private:
	void checkInput();
	void initUI();
	void setInitialMenuVisibility(bool visible);
	void setNewProfileMenuVisibility(bool visible);

	Tempest::Window* m_window;
	Tempest::GUI m_gui;
	Tempest::Camera2D m_camera;
	
	// initial menu
	CEGUI::PushButton* m_newProfileButton = nullptr;
	CEGUI::PushButton* m_loadProfileButton = nullptr;
	CEGUI::PushButton* m_exitButton = nullptr;
	CEGUI::GroupBox* m_initialGroupBox = nullptr;

	// new profile menu
	CEGUI::GroupBox* m_newProfileGroupBox = nullptr;
	CEGUI::Window* m_newProfileLabel = nullptr;
	CEGUI::Editbox* m_nameInput = nullptr;
	CEGUI::PushButton* m_createProfileButton = nullptr;
	CEGUI::PushButton* m_cancelNewProfile = nullptr;

	bool onExitClicked(const CEGUI::EventArgs& e);
	bool onNewProfileClicked(const CEGUI::EventArgs& e);
	bool onCancelNewProfileClicked(const CEGUI::EventArgs& e);
	bool onConfirmNewProfileClicked(const CEGUI::EventArgs& e);

};
