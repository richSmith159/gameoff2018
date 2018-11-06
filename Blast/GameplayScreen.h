#pragma once
#include "EntityRenderer.h"
#include "Player.h"
#include "PhysicsRenderer.h"
#include "EnemySquare.h"
#include "Spawner.h"

#include <Tempest\Window.h>
#include <Tempest\IGameScreen.h>
#include <Tempest\GUI.h>
#include <Tempest\Camera2D.h>

#include <Box2D\Box2D.h>

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

	bool m_renderDebug = true;

	void initUI();
	void checkInput();

	Tempest::Window* m_window;
	Tempest::GUI m_gui;
	Tempest::Camera2D m_camera;

	EntityRenderer m_entityRenderer;
	PhysicsRenderer m_physicsRenderer;
	Player m_player;

	Spawner<EnemySquare> m_squareSpawner;

	std::unique_ptr<b2World> m_world;
};
