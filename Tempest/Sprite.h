#pragma once
#include <GL\glew.h>
#include <string>
#include "glObjects.h"

namespace Tempest {

	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void init(float xPos, float yPos, float width, float height, std::string texturePath);

		void draw();

	private:
		int m_xPos;
		int m_yPos;
		float m_width;
		float m_height;
		GLuint m_vboID;
		glTexture m_texture;
	};

}