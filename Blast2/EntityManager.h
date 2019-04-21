#pragma once

#include <map>
#include "GameEntity.h"

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	GameEntity* getEntity(const int& entityID);
	void addEntity(TransformComponent* transform, PhysicsComponent* physics, SpriteComponent* sprite);
	void removeEntity(const int& entityID);

private:

	// rolling increment of number of entities used for entity ID
	int m_entityCount;

	std::map<int, GameEntity*> m_entities;

};

