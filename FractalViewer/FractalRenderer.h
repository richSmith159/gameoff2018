#pragma once

#include <Tempest\Camera2D.h>
#include <Tempest\GLSLProgram.h>
#include <Tempest\GLShader.h>
#include <Tempest\SpriteBatch.h>

#include "Fractal.h"

class FractalRenderer
{
public:
	FractalRenderer();
	~FractalRenderer();

	void init();
	void begin(Tempest::Camera2D* activeCamera);
	void render(Fractal* fractal);
	void end();

private:
	int m_drawWidth = 800;
	int m_drawHeight = 600;
	Tempest::SpriteBatch m_spriteBatch;
	Tempest::GLShader m_vertexShader;
	Tempest::GLShader m_fragmentShader;
	Tempest::GLSLProgram m_program;
};

