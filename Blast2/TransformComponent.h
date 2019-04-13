#pragma once

#include "IComponent.h"

#include <glm\glm\glm.hpp>


class TransformComponent : public IComponent
{
public:
	TransformComponent();
	~TransformComponent();

	virtual void onInsert() override;
	virtual void onRemove() override;
	
	glm::vec2 m_postition;

};

