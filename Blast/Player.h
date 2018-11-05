#pragma once

#include "Entity.h"

#include <Tempest\Camera2D.h>
#include <Tempest\InputManager.h>



class Player : public Entity
{
public:
	Player();
	~Player();

	void init(const int& lives, const float& speed, Tempest::InputManager* inputManager, Tempest::Camera2D* camera, const int& points);
	void update(float deltaTime);

private:
	
	int m_lives;
	float m_speed;
	int m_points = 0;

	Tempest::InputManager* m_inputManager;
	Tempest::Camera2D* m_camera;

};

