#include "GameEntity.h"

#include "PhysicsComponent.h"
#include "SpriteSystem.h"
#include "TransformComponent.h"



GameEntity::GameEntity(TransformComponent*, PhysicsComponent*, SpriteComponent*) {
	// empty
}


GameEntity::~GameEntity() {
	m_physicsComponent->enabled = false;
	m_spriteComponent->enabled = false;
	m_transformComponent->enabled = false;
}
