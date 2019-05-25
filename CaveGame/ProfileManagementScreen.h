#pragma once
#include <Tempest\Window.h>
#include <Tempest\IGameScreen.h>
#include <Tempest\GUI.h>
#include <Tempest\Camera2D.h>

#include "PlayerProfile.h"
#include "PlayerSerializer.h"


class ProfileManagementScreen : public Tempest::IGameScreen
{
public:
	ProfileManagementScreen(Tempest::Window* window);
	~ProfileManagementScreen();

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

	bool onPlayNextPressed();

	Tempest::Window* m_window;
	Tempest::GUI m_gui;
	Tempest::Camera2D m_camera;

	PlayerProfile m_currentProfile;
	PlayerSerializer m_playerSerializer;

	CEGUI::GroupBox* m_profileStatsGroupBox = nullptr;
	CEGUI::GroupBox* m_charactersGroupBox = nullptr;

	CEGUI::PushButton* m_playNextMapButton = nullptr;

};