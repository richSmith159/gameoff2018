#pragma once

#include <memory>
#include <Tempest\Window.h>
#include <Tempest\IGameScreen.h>
#include <Tempest\GUI.h>
#include <Tempest\Camera2D.h>

#include "CaveMap.h"
#include "SimpleRenderer.h"


class CaveGenerationScreen : public Tempest::IGameScreen
{
public:
	CaveGenerationScreen(Tempest::Window* window);
	~CaveGenerationScreen();
	virtual int getNextIndex() const override;
	virtual int getPrevIndex() const override;
	virtual void build() override;
	virtual void destroy() override;
	virtual void onEntry() override;
	virtual void onExit() override;
	virtual void update(float deltaTime) override;
	virtual void draw() override;
private:
	void checkInput();
	void initUI();

	Tempest::Window* m_window;
	Tempest::GUI m_gui;
	Tempest::Camera2D m_camera;

	CaveMap m_caveMap;
	SimpleRenderer m_renderer;


	CEGUI::PushButton* m_testButton = nullptr;
	CEGUI::GroupBox* m_groupBox = nullptr;

};

