#pragma once
#include "IComponent.h"
#include <Tempest\GLObjects.h>
#include <glm\glm\glm.hpp>


class SpriteComponent : public IComponent
{
public:
	SpriteComponent(Tempest::glTexture texture, Tempest::ColorRGBA8 color, float width, float height);
	~SpriteComponent();

	virtual void onInsert() override;
	virtual void onRemove() override;
	glm::vec4 calculateDestRect();

	float m_height;
	float m_width;
	Tempest::glTexture m_texture;
	Tempest::ColorRGBA8 m_color;
};

