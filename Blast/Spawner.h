#pragma once
#include "Player.h"

#include <Tempest\GLObjects.h>

#include <glm\glm\glm.hpp>
#include <random>
#include <vector>

template <class T>
class Spawner {
public:
	void init(float spawnRate, float spawnHealth, float spawnSpeed, Player* player);
	void update();
	void spawn(
		glm::vec2 position,
		float health,
		float speed,
		Player* player
	);
	std::vector<T> m_entities;
	float m_spawnRate;
	float m_spawnHealth;
	float m_spawnSpeed;
	Player* m_playerHandle;
};

template <class T>
void Spawner<T>::init(float spawnRate, float spawnHealth, float spawnSpeed, Player* player) {
	m_spawnRate = spawnRate;
	m_spawnHealth = spawnHealth;
	m_spawnSpeed = spawnSpeed;
	m_playerHandle = player;
}

template <class T>
void Spawner<T>::spawn(
	glm::vec2 position,
	float health,
	float speed,
	Player* player
) {
	T newEntity;
	newEntity.init(position, health, speed, player);
	m_entities.push_back(newEntity);
}

template <class T>
void Spawner<T>::update() {
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
			m_playerHandle
		);
	}
}
