#pragma once

#include "ISystem.h"
#include "PhysicsComponent.h"

#include <glm\glm\glm.hpp>


class PhysicsSystem : public ISystem<PhysicsComponent>
{
public:
	PhysicsSystem();
	~PhysicsSystem();

	void initSystem(float gravityX, float gravityY);
	virtual void run(float deltaTime) override;
	PhysicsComponent* addComponent(b2BodyType bodyType, glm::vec2 boundingDims, float xPos, float yPos, float angle);


private:

	std::unique_ptr<b2World> m_world;


};

