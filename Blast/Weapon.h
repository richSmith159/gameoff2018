#pragma once

#include <string>

class Weapon
{
public:
	Weapon();
	~Weapon();

	void update(float deltaTime);

private:

	void fire();

	std::string m_name;



};

