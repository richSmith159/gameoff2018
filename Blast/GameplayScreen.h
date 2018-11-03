#pragma once
#include "EntityRenderer.h"
#include "Player.h"
#include "EnemySquare.h"

#include <Tempest\Window.h>
#include <Tempest\IGameScreen.h>
#include <Tempest\GUI.h>
#include <Tempest\Camera2D.h>

class GameplayScreen : public Tempest::IGameScreen
{
public:
	GameplayScreen(Tempest::Window* window);
	~GameplayScreen();

	virtual int getNextIndex() const override;
	virtual int getPrevIndex() const override;
	virtual void build() override;
	virtual void destroy() override;
	virtual void onEntry() override;
	virtual void onExit() override;
	virtual void update(float deltaTime) override;
	virtual void draw() override;

private:

	void initUI();
	void checkInput();

	Tempest::Window* m_window;
	Tempest::GUI m_gui;
	Tempest::Camera2D m_camera;

	Player m_player;
	EntityRenderer m_entityRenderer;
	EnemySquare m_testSquare;
};
