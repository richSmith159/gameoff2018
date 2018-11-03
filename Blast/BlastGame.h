#pragma once
#include "GameplayScreen.h"

#include <Tempest\IMainGame.h>


class BlastGame: public Tempest::IMainGame
{
public:
	BlastGame();
	~BlastGame();

	virtual void onInit() override;
	virtual void addScreens() override;
	virtual void onExit() override;

private:

	std::unique_ptr<GameplayScreen> m_gameplayScreen = nullptr;

};

