#pragma once

#include "Enemy.h"

class EnemyCircle : public Enemy
{
public:
	EnemyCircle(glm::vec2 position, float health, float speed, Player* player, b2World* physicsWorld);
	~EnemyCircle();

	// void init(glm::vec2 position, float health, float speed, Player* player, b2World* physicsWorld) override;
	void update(float deltaTime) override;

private:

	float m_rateOfConvergence = 0.999f;

};
