#include "Weapon.h"

#include <iostream>


Weapon::Weapon() {
	// empty
}

Weapon::~Weapon() {
	// empty
}

void Weapon::init(const std::string & name, const int & fireRate, const float & range, const int & bulletsPerShot, const float & bulletSpeed, const float & bulletDamage, const float & bulletWidth, const float & bulletHeight, const Tempest::glTexture & bulletTexture) {

	// weapon properties
	m_fireRate = fireRate;
	m_frameCounter = 0;
	m_range = range;
	m_name = name;

	// bullet properties
	m_bulletsPerShot = bulletsPerShot;
	m_bulletSpeed = bulletSpeed;
	m_bulletDamage = bulletDamage;
	m_bulletWidth = bulletWidth;
	m_bulletHeight = bulletHeight;
	m_bulletTexture = bulletTexture;

}

void Weapon::update(bool mouseDown, const glm::vec2 & position, const glm::vec2 & direction, float deltaTime) {
	m_frameCounter += 1.0f * deltaTime;
	if (m_frameCounter >= m_fireRate && mouseDown) {
		fire(direction, position);
		m_frameCounter = 0;
	}
}

void Weapon::fire(const glm::vec2 & direction, const glm::vec2 & position) {
	std::cout << "FIRE " << m_bulletsPerShot << std::endl;
	for (int i = 0; i < m_bulletsPerShot; i++) {
		m_bullets.emplace_back(
			position - glm::vec2(m_bulletWidth/2.0f, m_bulletHeight / 2.0f),
			direction,
			m_bulletTexture,
			m_bulletWidth,
			m_bulletHeight,
			m_bulletDamage,
			m_bulletSpeed,
			m_range
		);
	}

}
