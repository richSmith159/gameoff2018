#pragma once

#include "GameEntity.h"

class IComponent
{
public:
	IComponent();
	~IComponent();

	virtual void onInsert() = 0;
	virtual void onRemove() = 0;

	bool enabled = true;
	GameEntity* m_entity = nullptr;

};

