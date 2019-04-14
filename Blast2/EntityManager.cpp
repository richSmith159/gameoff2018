#include "EntityManager.h"

#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"

#include <iostream>


EntityManager::EntityManager() {
	// empty
}


EntityManager::~EntityManager() {
	// empty
}

GameEntity * EntityManager::getEntity(const int & entityID) {
	auto mapIterator = m_entities.find(entityID);
	if (mapIterator == m_entities.end()) {
		return nullptr;
	}
	return &mapIterator->second;
}

void EntityManager::addEntity(TransformComponent * transform, PhysicsComponent * physics, SpriteComponent * sprite) {
	
	// create new entity
	GameEntity newEntity;	
	newEntity.m_id = m_entityCount;

	// set reverse pointer relation
	if (physics != nullptr) {
		newEntity.m_physicsComponent = physics;
		physics->m_entity = &newEntity;
	}
	if (transform != nullptr) {
		newEntity.m_transformComponent = transform;
		sprite->m_entity = &newEntity;
	}
	if (sprite != nullptr) {
		newEntity.m_spriteComponent = sprite;
		sprite->m_entity = &newEntity;
	}
	
	// insert into map
	std::pair<int, GameEntity> newPair(m_entityCount, newEntity);
	m_entities.insert(newPair);

	m_entityCount++;

}

void EntityManager::removeEntity(const int & entityID) {
	auto mapIterator = m_entities.find(entityID);
	if (mapIterator != m_entities.end()) {
		m_entities.erase(mapIterator);
	}
}
