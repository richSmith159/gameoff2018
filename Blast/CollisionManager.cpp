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
	std::cout << "called" << std::endl;
	void* fixtureABodyData = contact->GetFixtureA()->GetBody()->GetUserData();
	void* fixtureBBodyData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (fixtureABodyData && fixtureBBodyData) {
		Entity* fixtureAEntity = static_cast<Entity*>(fixtureABodyData);
		Entity* fixtureBEntity = static_cast<Entity*>(fixtureBBodyData);
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
	Bullet* bullet = static_cast<Bullet*>(bulletEntity);
	Enemy* enemy = static_cast<Enemy*>(enemyEntity);
	enemy->applyDamage(bullet->getDamage());
	bullet->setCollided(true);
}
