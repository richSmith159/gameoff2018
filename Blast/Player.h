#pragma once

#include "Entity.h"
#include "Boundary.h"

#include <Tempest\Camera2D.h>
#include <Tempest\InputManager.h>



class Player : public Entity
{
public:
	Player();
	~Player();

	void init(const int& lives, const float& speed, Tempest::InputManager* inputManager, Tempest::Camera2D* camera, const int& points, const int& abilities);
	void update(float deltaTime, Boundary* boundary);
	void incrementAbilities(const int& offset) { m_remainingAbilities += offset; }

private:
	
	int m_lives;
	float m_speed;
	int m_points = 0;
	int m_remainingAbilities = 3;

	Tempest::InputManager* m_inputManager;
	Tempest::Camera2D* m_camera;

};

