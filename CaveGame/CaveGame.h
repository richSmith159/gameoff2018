#pragma once

#include <Tempest\IMainGame.h>
#include "CaveGenerationScreen.h"
#include "MainMenuScreen.h"
#include "ProfileManagementScreen.h"


class CaveGame : public Tempest::IMainGame
{
public:
	CaveGame();
	~CaveGame();

	virtual void onInit() override;
	virtual void addScreens() override;
	virtual void onExit() override;


	bool m_loadProfile = false;
	bool m_createProfile = false;

private:

	std::unique_ptr<CaveGenerationScreen> m_caveGenerationScreen = nullptr;
	std::unique_ptr<MainMenuScreen> m_mainMenuScreen = nullptr;
	std::unique_ptr<ProfileManagementScreen> m_profileManagementScreen = nullptr;

};
