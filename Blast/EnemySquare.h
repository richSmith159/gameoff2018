#pragma once
#include "Enemy.h"
#include "Player.h"

#include <Tempest\GLObjects.h>


class EnemySquare : public Enemy
{
public:
	EnemySquare();
	~EnemySquare();

	void init(glm::vec2 position, int health, int speed, Player* player);
	void update(float deltaTime) override;
	
};
