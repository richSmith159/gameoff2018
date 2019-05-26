#include "LineRenderer.h"

namespace Tempest {

	const char* VERTEX_SHADER_SOURCE = R"(
		#version 130
		in vec2 vertexPosition;
		in vec4 vertexColor;
		out vec2 fragmentPosition;
		out vec4 fragmentColor;
		uniform mat4 P;
		void main() {
			gl_Position.xy = (P * vec4(vertexPosition, 0.0, 1.0)).xy;
			gl_Position.z = 0.0;
			gl_Position.w = 1.0;
			fragmentPosition = vertexPosition;
			fragmentColor = vertexColor;
		}
	)";

	const char* FRAGMENT_SHADER_SOURCE = R"(
		#version 130
		in vec2 fragmentPosition;
		in vec4 fragmentColor;
		out vec4 color;
		void main() {
			color = fragmentColor;
		}
	)";


	LineRenderer::LineRenderer() {
		// empty
	}


	LineRenderer::~LineRenderer() {
		dispose();
	}

	void LineRenderer::init() {
		
		// init the shader program and spritebatch
		m_program.init();

		// init and compile shaders
		m_vertexShader.init(Tempest::ShaderType::VERTEX);
		m_fragmentShader.init(Tempest::ShaderType::FRAGMENT);
		m_vertexShader.compile(VERTEX_SHADER_SOURCE);
		m_fragmentShader.compile(FRAGMENT_SHADER_SOURCE);

		// bind shader attributes and link shaders
		m_program.bindAttribute("vertextPosition");
		m_program.bindAttribute("vertexColor");
		m_program.linkShaders(m_vertexShader.getShaderID(), m_fragmentShader.getShaderID());

		// Set up buffers
		glGenVertexArrays(1, &m_vaoID);
		glGenBuffers(1, &m_vboID);
		glGenBuffers(1, &m_iboID);

		glBindVertexArray(m_vaoID);
		glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboID);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(DebugVertex), (void*)offsetof(DebugVertex, position));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(DebugVertex), (void*)offsetof(DebugVertex, color));

		glBindVertexArray(0);
	}

	void LineRenderer::begin(Tempest::Camera2D * camera, float lineWidth) {
		m_program.use();

		glm::mat4 projectionMatrix = camera->getCameraMatrix();
		GLint pUniform = m_program.getUniformLocation("P");
		glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

		glLineWidth(lineWidth);

	}

	void LineRenderer::end() {
		glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
		glBufferData(GL_ARRAY_BUFFER, m_verts.size() * sizeof(DebugVertex), nullptr, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_verts.size() * sizeof(DebugVertex), m_verts.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), nullptr, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_indices.size() * sizeof(GLuint), m_indices.data());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		m_numElements = m_indices.size();
		m_indices.clear();
		m_verts.clear();

		glBindVertexArray(m_vaoID);
		glDrawElements(GL_LINES, m_numElements, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		m_program.unuse();

	}

	void LineRenderer::drawLine(glm::vec2 startPoint, glm::vec2 endPoint, Tempest::ColorRGBA8 color) {
		int numVerts = m_verts.size();
		m_verts.resize(numVerts + 2);
		m_verts[numVerts].position = startPoint;
		m_verts[numVerts].color = color;
		m_verts[numVerts + 1].position = endPoint;
		m_verts[numVerts + 1].color = color;

		m_indices.push_back(numVerts);
		m_indices.push_back(numVerts + 1);

	}

	void LineRenderer::drawSquare(glm::vec4 destRect, Tempest::ColorRGBA8 color, glm::vec2 direction) {
		// calculate angle
		const glm::vec2 right(1.0f, 0.0f);
		float angle = acos(glm::dot(right, direction));
		if (direction.y < 0) {
			angle = -angle;
		}

		int numVerts = m_verts.size();
		m_verts.resize(numVerts + 4);

		glm::vec2 halfDimensions(destRect.z / 2.0f, destRect.w / 2.0f);

		// Get points centered at origin
		glm::vec2 tl(-halfDimensions.x, halfDimensions.y);
		glm::vec2 bl(-halfDimensions.x, -halfDimensions.y);
		glm::vec2 br(halfDimensions.x, -halfDimensions.y);
		glm::vec2 tr(halfDimensions.x, halfDimensions.y);

		glm::vec2 positionOffset(destRect.x, destRect.y);


		// Rotate the points
		m_verts[numVerts].position = rotatePoint(tl, angle) + halfDimensions + positionOffset;
		m_verts[numVerts + 1].position = rotatePoint(bl, angle) + halfDimensions + positionOffset;
		m_verts[numVerts + 2].position = rotatePoint(br, angle) + halfDimensions + positionOffset;
		m_verts[numVerts + 3].position = rotatePoint(tr, angle) + halfDimensions + positionOffset;

		for (int j = numVerts; j < numVerts + 4; j++) {
			m_verts[j].color = color;
		}

		m_indices.reserve(m_indices.size() + 8);

		m_indices.push_back(numVerts);
		m_indices.push_back(numVerts + 1);

		m_indices.push_back(numVerts + 1);
		m_indices.push_back(numVerts + 2);

		m_indices.push_back(numVerts + 2);
		m_indices.push_back(numVerts + 3);

		m_indices.push_back(numVerts + 3);
		m_indices.push_back(numVerts);

	}

	void LineRenderer::dispose() {

		if (m_vaoID) {
			glDeleteVertexArrays(1, &m_vaoID);
		}
		if (m_vboID) {
			glDeleteBuffers(1, &m_vboID);
		}
		if (m_iboID) {
			glDeleteBuffers(1, &m_iboID);
		}
		m_program.dispose();

	}

	glm::vec2 LineRenderer::rotatePoint(glm::vec2 center, float angle) {
		return glm::vec2(
			center.x * cos(angle) - center.y * sin(angle),
			center.x * sin(angle) + center.y * cos(angle)
		);
	}



}
