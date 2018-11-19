#pragma once
#include "Player.h"

#include <Tempest\GLObjects.h>

#include <Box2D\Box2D.h>
#include <glm\glm\glm.hpp>
#include <random>
#include <vector>

template <class T>
class Spawner {
public:
	void init(float spawnRate, float spawnHealth, float spawnSpeed, Player* player, b2World* physicsWorld);
	void update();
	void spawn(
		glm::vec2 position,
		float health,
		float speed,
		Player* player,
		b2World* physicsWorld
	);
	std::vector<T> m_entities;
	float m_spawnRate;
	float m_spawnHealth;
	float m_spawnSpeed;
	Player* m_playerHandle;
	b2World* m_world;
};

template <class T>
void Spawner<T>::init(float spawnRate, float spawnHealth, float spawnSpeed, Player* player, b2World* physicsWorld) {
	m_spawnRate = spawnRate;
	m_spawnHealth = spawnHealth;
	m_spawnSpeed = spawnSpeed;
	m_playerHandle = player;
	m_world = physicsWorld;
}

template <class T>
void Spawner<T>::spawn(
	glm::vec2 position,
	float health,
	float speed,
	Player* player,
	b2World* physicsWorld
) {
	T newEntity;
	newEntity.init(position, health, speed, player, physicsWorld);
	m_entities.push_back(newEntity);
}

template <class T>
void Spawner<T>::update() {
	if (m_entities.size() <= 0) {
		std::random_device rd;
		std::mt19937 randGenerator(rd());
		std::uniform_real_distribution<float> randomNumber(0.0f, 1.0f);
		if (randomNumber(randGenerator) < m_spawnRate) {
			std::uniform_real_distribution<float> positionDistribution(-200.0f, 200.0f);
			spawn(
				glm::vec2(
					positionDistribution(randGenerator),
					positionDistribution(randGenerator)
				),
				m_spawnHealth,
				m_spawnSpeed,
				m_playerHandle,
				m_world
			);
		}
	}
}
