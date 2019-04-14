#pragma once

#include "ISystem.h"
#include "SpriteComponent.h"
#include "SpriteRenderer.h"

class SpriteSystem : public ISystem<SpriteComponent>
{
public:
	SpriteSystem();
	~SpriteSystem();

	virtual void run(float deltaTime) override;
	
	void initSystem(Tempest::Camera2D* camera);
	SpriteComponent* addComponent(Tempest::glTexture texture, Tempest::ColorRGBA8 color, float width, float height);
	void removeComponent();

	inline void setRenderer(SpriteRenderer* renderer) { m_renderer = renderer; }

	SpriteRenderer* m_renderer;
	Tempest::Camera2D* m_cameraHandle = nullptr;

};

