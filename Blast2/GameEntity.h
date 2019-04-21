#pragma once


class TransformComponent;
class SpriteComponent;
class PhysicsComponent;


class GameEntity
{
public:
	GameEntity(TransformComponent*, PhysicsComponent*, SpriteComponent*);
	~GameEntity();

	TransformComponent* m_transformComponent = nullptr;
	PhysicsComponent* m_physicsComponent = nullptr;
	SpriteComponent* m_spriteComponent = nullptr;

	int m_id;

};
