#pragma once
#include "Bullet.h"

#include <glm/glm/gtx/rotate_vector.hpp>
#include <glm\glm\glm.hpp>
#include <ctime>
#include <random>
#include <string>
#include <vector>

class Weapon
{
public:
	Weapon();
	~Weapon();

	void init(
		const std::string& name,
		const int& fireRate,
		const float& range,
		const int& bulletsPerShot,
		const float& bulletSpeed,
		const float& bulletDamage,
		const float& bulletWidth,
		const float& bulletHeight,
		const Tempest::glTexture& bulletTexture
	);

	void update(
		bool mouseDown,
		const glm::vec2& position,
		const glm::vec2& direction,
		float deltaTime
	);

	// bullets (public for better access)
	std::vector<Bullet> m_bullets;

private:

	void fire(const glm::vec2& direction, const glm::vec2& position);

	// weapon properties
	int m_fireRate;
	float m_frameCounter;
	float m_range;
	std::string m_name;

	// bullet properties
	int m_bulletsPerShot;
	float m_bulletSpeed;
	float m_bulletDamage;
	float m_bulletWidth;
	float m_bulletHeight;
	Tempest::glTexture m_bulletTexture;
	
};
