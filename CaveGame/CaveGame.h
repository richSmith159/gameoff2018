#pragma once

#include <Tempest\IMainGame.h>

#include "CaveGenerationScreen.h"

class CaveGame : public Tempest::IMainGame
{
public:
	CaveGame();
	~CaveGame();

	virtual void onInit() override;
	virtual void addScreens() override;
	virtual void onExit() override;

private:

	std::unique_ptr<CaveGenerationScreen> m_caveGenerationScreen = nullptr;

};
