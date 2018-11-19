#include "CollisionManager.h"
#include "Entity.h"
#include <iostream>


CollisionManager::CollisionManager() {
	// empty
}

CollisionManager::~CollisionManager() {
	// empty
}

void CollisionManager::BeginContact(b2Contact * contact) {

	void* fixtureABodyData = contact->GetFixtureA()->GetBody()->GetUserData();
	void* fixtureBBodyData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (fixtureABodyData && fixtureBBodyData) {
		Entity* fixtureAData = static_cast<Entity*>(fixtureABodyData);
		Entity* fixtureBData = static_cast<Entity*>(fixtureBBodyData);
		if (fixtureAData->getCollisionObjectType() == COLLISION_OBJECT_TYPE::BULLET) {
			std::cout << "A BULLET" << std::endl;
		}
		if (fixtureBData->getCollisionObjectType() == COLLISION_OBJECT_TYPE::BULLET) {
			std::cout << "B BULLET" << std::endl;
		}
		if (fixtureAData->getCollisionObjectType() == COLLISION_OBJECT_TYPE::ENEMY) {
			std::cout << "A ENEMY" << std::endl;
		}
		if (fixtureBData->getCollisionObjectType() == COLLISION_OBJECT_TYPE::ENEMY) {
			std::cout << "B ENEMY" << std::endl;
		}
		std::cout << "----------------------" << std::endl;
		/*
		if (
			fixtureAEntity->getCollisionObjectType() == COLLISION_OBJECT_TYPE::BULLET &&
			fixtureBEntity->getCollisionObjectType() == COLLISION_OBJECT_TYPE::ENEMY
		) {
			handleBulletEnemyCollision(fixtureAEntity, fixtureBEntity);
		}
		else if (
			fixtureAEntity->getCollisionObjectType() == COLLISION_OBJECT_TYPE::ENEMY &&
			fixtureBEntity->getCollisionObjectType() == COLLISION_OBJECT_TYPE::BULLET
		) {
			handleBulletEnemyCollision(fixtureBEntity, fixtureAEntity);
		}
		*/
	}
}

void CollisionManager::EndContact(b2Contact* contact) {
	// empty
}

void CollisionManager::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
	// empty
}

void CollisionManager::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
	// empty
}

void CollisionManager::handleBulletEnemyCollision(Entity * bulletEntity, Entity * enemyEntity) {
	std::cout << "called" << std::endl;
	Bullet* bullet = static_cast<Bullet*>(bulletEntity);
	Enemy* enemy = static_cast<Enemy*>(enemyEntity);
	enemy->applyDamage(bullet->getDamage());
	bullet->setCollided(true);
}
