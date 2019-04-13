#pragma once
#include "GameScreen.h"

#include <Tempest\IMainGame.h>


class Blast2Game : public Tempest::IMainGame
{
public:
	Blast2Game();
	~Blast2Game();

	virtual void onInit() override;
	virtual void addScreens() override;
	virtual void onExit() override;

private:

	std::unique_ptr<GameScreen> m_gameScreen = nullptr;

};

