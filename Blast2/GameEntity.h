#pragma once

// #include "TransformComponent.h"
// #include "SpriteComponent.h"
// #include "PhysicsComponent.h"


class TransformComponent;
class SpriteComponent;
class PhysicsComponent;


class GameEntity
{
public:
	GameEntity();
	~GameEntity();

	TransformComponent* m_transformComponent = nullptr;
	PhysicsComponent* m_physicsComponent = nullptr;
	SpriteComponent* m_spriteComponent = nullptr;

	int m_id;

};
