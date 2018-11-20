#include "Boundary.h"

#include <iostream>


Boundary::Boundary() {
	// empty
}


Boundary::~Boundary() {
	// empty
}

void Boundary::init(glm::vec2 position, float size, float decreaseRate, Tempest::glTexture texture) {
	m_position = position;
	m_width = size;
	m_height = size;
	m_texture = texture;
	m_decreaseRate = decreaseRate;
	m_color = Tempest::ColorRGBA8(255.0f, 255.0f, 255.0f, 255.0f);
}

void Boundary::update(float deltaTime) {
	float delta = m_decreaseRate * deltaTime;
	m_width -= delta;
	m_height -= delta;
	m_position = glm::vec2(-m_width * 0.5f, -m_height * 0.5f);
}
