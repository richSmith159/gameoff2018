#pragma once

#include <Box2D\Box2D.h>

#include "IComponent.h"


class PhysicsComponent : public IComponent
{
public:
	PhysicsComponent(b2BodyType bodyType, float xPos, float yPos, float angle, b2World* physicsWorldHandle);
	~PhysicsComponent();

	virtual void onInsert() override;
	virtual void onRemove() override;

	b2Body* m_body = nullptr;
	b2Fixture* m_fixtures[3];
	b2World* m_physicsWorldHandle;

	int lol = 123;
};

