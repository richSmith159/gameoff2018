#pragma once
#include "Enemy.h"
#include "Player.h"

#include <Tempest\GLObjects.h>


class EnemySquare : public Enemy
{
public:
	EnemySquare();
	~EnemySquare();

	void init(glm::vec2 position, float health, float speed, Player* player) override;
	void update(float deltaTime) override;
	
};
