#pragma once

#include <string>
#include <glm\glm\glm.hpp>

class Character
{
public:
	Character();
	~Character();

protected:
	std::string m_name;
	glm::vec2 m_position;

	int m_health;
	float m_speed;
};

