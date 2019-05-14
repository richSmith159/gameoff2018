#pragma once

#include <Tempest\Window.h>
#include <Tempest\IGameScreen.h>
#include <Tempest\GUI.h>
#include <Tempest\Camera2D.h>
#include "FractalRenderer.h"

#include "Fractal.h"


class FractalScreen : public Tempest::IGameScreen
{
public:
	FractalScreen(Tempest::Window* window);
	~FractalScreen();

	virtual int getNextIndex() const override;
	virtual int getPrevIndex() const override;
	virtual void build() override;
	virtual void destroy() override;
	virtual void onEntry() override;
	virtual void onExit() override;
	virtual void update(float deltaTime) override;
	virtual void draw() override;

private:
	void initUI();
	void checkInput();

	Tempest::Window* m_window;
	Tempest::GUI m_gui;
	Tempest::Camera2D m_camera;

	FractalRenderer m_fractalRenderer;

	Fractal m_fractal;
	float m_timeCount = 0.0f;

};

