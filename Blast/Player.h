#pragma once

#include "Entity.h"

#include <Tempest\Camera2D.h>
#include <Tempest\InputManager.h>



class Player : public Entity
{
public:
	Player();
	~Player();

	void update(float deltaTime);

private:
	
	int m_lives;
	float m_speed;
	int m_points = 0;

	Tempest::InputManager* m_inputManager;
	Tempest::Camera2D* m_camera;

};

