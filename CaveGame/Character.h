#pragma once

#include <glm\glm\glm.hpp>

class Character
{
public:
	Character();
	~Character();
private:
	char* m_name;
	int m_health;
	glm::vec2 m_position;
	
};

