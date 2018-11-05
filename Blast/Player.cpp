#include "Player.h"

#include <Tempest\ResourceManager.h>

#include <glm\glm\glm.hpp>
#include <SDL\SDL.h>


Player::Player() {
	// empty
}


Player::~Player() {
	// empty
}

void Player::init(
	const int & lives,
	const float & speed,
	Tempest::InputManager * inputManager,
	Tempest::Camera2D * camera,
	const int & points) {
	m_speed = speed;
	m_lives = lives;
	m_inputManager = inputManager;
	m_camera = camera;
	m_points = points;
	m_texture = Tempest::ResourceManager::getTexture("Assets/Textures/Entities/player.png");
	m_width = 16;
	m_height = 16;
	m_color = Tempest::ColorRGBA8(255, 255, 255, 255);
}

void Player::update(float deltaTime) {

	glm::vec2 mouseCoords = m_inputManager->getMouseCoords();
	mouseCoords = m_camera->convertScreenToWorld(mouseCoords);
	m_direction = glm::normalize(mouseCoords - getCenterPosition());

	if (m_inputManager->isKeyDown(SDLK_w)) {
		m_position += m_direction * m_speed * deltaTime;
	}
	if (m_inputManager->isKeyDown(SDLK_s)) {
		m_position -= m_direction * m_speed * deltaTime;
	}
	
	// TODO: check functionality is intuitive
	if (m_inputManager->isKeyDown(SDLK_a)) {
		m_position.x -= m_speed * deltaTime;
	}
	if (m_inputManager->isKeyDown(SDLK_d)) {
		m_position.x += m_speed * deltaTime;
	}

	// TODO: pause screen
	if (m_inputManager->isKeyDown(SDLK_ESCAPE)) { exit(69); }

}
