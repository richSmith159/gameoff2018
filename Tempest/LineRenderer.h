#pragma once
#include <glm\glm\glm.hpp>
#include <vector>
#include "Camera2D.h"
#include "GLObjects.h"
#include "GLSLProgram.h"
#include "GLShader.h"

namespace Tempest {

	struct DebugVertex {
		glm::vec2 position;
		Tempest::ColorRGBA8 color;
	};

	class LineRenderer
	{
	public:
		LineRenderer();
		~LineRenderer();
		void init();
		void begin(Tempest::Camera2D* camera, float lineWidth);
		void end();
		void drawLine(glm::vec2 startPoint, glm::vec2 endPoint, Tempest::ColorRGBA8 color);
		void drawSquare(glm::vec4 destRect, Tempest::ColorRGBA8 color, glm::vec2 direction);
		void dispose();
	private:

		glm::vec2 rotatePoint(glm::vec2 center, float angle);

		Tempest::GLShader m_vertexShader;
		Tempest::GLShader m_fragmentShader;
		Tempest::GLSLProgram m_program;
		std::vector<DebugVertex> m_verts;
		std::vector<GLuint> m_indices;
		GLuint m_vboID = 0, m_vaoID = 0, m_iboID = 0;
		int m_numElements = 0;
	};

}

