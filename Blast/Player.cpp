#include "Player.h"

#include <glm\glm\glm.hpp>
#include <SDL\SDL.h>


Player::Player() {
	// empty
}


Player::~Player() {
	// empty
}

void Player::update(float deltaTime) {

	glm::vec2 mouseCoords = m_inputManager->getMouseCoords();
	mouseCoords = m_camera->convertScreenToWorld(mouseCoords);
	
	m_direction = glm::normalize(mouseCoords - m_position);

	if (m_inputManager->isKeyDown(SDLK_w)) {
		m_position.y += m_speed * deltaTime;
	}
	if (m_inputManager->isKeyDown(SDLK_s)) {
		m_position.y -= m_speed * deltaTime;
	}
	if (m_inputManager->isKeyDown(SDLK_a)) {
		m_position.x -= m_speed * deltaTime;
	}
	if (m_inputManager->isKeyDown(SDLK_d)) {
		m_position.x += m_speed * deltaTime;
	}

}
