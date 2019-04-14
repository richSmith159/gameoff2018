#pragma once

#include "SpriteSystem.h"
#include "PhysicsSystem.h"
#include "EntityManager.h"

#include <Tempest\Window.h>
#include <Tempest\IGameScreen.h>
#include <Tempest\GUI.h>
#include <Tempest\Camera2D.h>

#include <Box2D\Box2D.h>

class GameScreen : public Tempest::IGameScreen
{
public:
	GameScreen(Tempest::Window* window);
	~GameScreen();

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
	void spawnEnemy(const std::string& spriteTexturePath, glm::vec2 initialPosition, const float& width, const float& height);

	Tempest::Window* m_window;
	Tempest::GUI m_gui;
	Tempest::Camera2D m_camera;

	SpriteSystem m_spriteSystem;
	PhysicsSystem m_physicsSystem;

	EntityManager m_entityManager;
	SpriteRenderer m_defaultRenderer;

};
