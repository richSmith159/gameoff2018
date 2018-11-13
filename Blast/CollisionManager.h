#pragma once
#include "Bullet.h"
#include "EnemySquare.h"

#include <Box2D\Box2D.h>
#include <vector>

class CollisionManager : public b2ContactListener
{
public:
	CollisionManager();
	~CollisionManager();

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

private:

	// collision condition handlers
	void handleBulletEnemyCollision(Entity* bulletEntity, Entity* enemyEntity);

	int m_playerCollisionCount;
	std::vector<Bullet*> m_bulletsToRemove;
	std::vector<EnemySquare*> m_squaresToRemove;

};

