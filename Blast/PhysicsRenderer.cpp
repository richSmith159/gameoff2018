#include "PhysicsRenderer.h"

#include <iostream>


const char* PHYSICS_VERTEX_SHADER_SOURCE = R"(
#version 330
//input data from the VBO. Each vertex is 2 floats
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

const char* PHYSICS_FRAGMENT_SHADER_SOURCE = R"(
#version 330
in vec2 fragmentPosition;
in vec4 fragmentColor;
out vec4 color;
void main() {
    color = fragmentColor;
}
)";



PhysicsRenderer::PhysicsRenderer() {
	// empty
}


PhysicsRenderer::~PhysicsRenderer() {
	dispose();
}

void PhysicsRenderer::init() {
	// init the shader program
	m_program.init();

	// init and compile shaders
	m_vertexShader.init(Tempest::ShaderType::VERTEX);
	m_fragmentShader.init(Tempest::ShaderType::FRAGMENT);
	m_vertexShader.compile(PHYSICS_VERTEX_SHADER_SOURCE);
	m_fragmentShader.compile(PHYSICS_FRAGMENT_SHADER_SOURCE);

	// bind shader attributes and link shaders
	m_program.bindAttribute("vertextPosition");
	m_program.bindAttribute("vertexColor");
	m_program.linkShaders(m_vertexShader.getShaderID(), m_fragmentShader.getShaderID());

	// Set up buffers
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(DebugVertex), (void*)offsetof(DebugVertex, position));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(DebugVertex), (void*)offsetof(DebugVertex, color));

	glBindVertexArray(0);
}

void PhysicsRenderer::begin(Tempest::Camera2D * activeCamera) {

	// use the program and set the texture uniform location
	m_program.use();

	// get the camera's projection matrix (2D so orthographic)
	glm::mat4 projectionMatrix = activeCamera->getCameraMatrix();
	GLint pUniform = m_program.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);
}

void PhysicsRenderer::drawSquare(b2Body * body, Tempest::ColorRGBA8 color) {
	int startIndex = m_verts.size();
	m_verts.resize(m_verts.size() + 4);
	b2Fixture fixture = body->GetFixtureList()[0];
	b2PolygonShape* shape = (b2PolygonShape*)fixture.GetShape();
	for (int i = 0; i < 4; i++) {
		b2Vec2 worldVertPos = body->GetWorldPoint(shape->m_vertices[i]);
		m_verts[startIndex + i].position.x = worldVertPos.x;
		m_verts[startIndex + i].position.y = worldVertPos.y;
		m_verts[startIndex + i].color = color;
	}

	m_indices.reserve(m_indices.size() + 8);
	m_indices.push_back(startIndex);
	m_indices.push_back(startIndex + 1);

	m_indices.push_back(startIndex + 1);
	m_indices.push_back(startIndex + 2);

	m_indices.push_back(startIndex + 2);
	m_indices.push_back(startIndex + 3);

	m_indices.push_back(startIndex + 3);
	m_indices.push_back(startIndex);


}

void PhysicsRenderer::draw(b2Body * body, Tempest::ColorRGBA8 color) {
	
	for (b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext()) {
		int startIndex = m_verts.size();
		switch (fixture->GetType()) {
		default:
			b2PolygonShape* shape = (b2PolygonShape*)fixture->GetShape();
			int numberOfVerts = shape->m_vertices->Length();
			m_verts.resize(startIndex + numberOfVerts);
			for (unsigned int i = 0; i < numberOfVerts; i++) {
				b2Vec2 worldVertPos = body->GetWorldPoint(shape->m_vertices[i]);
				m_verts[startIndex + i].position.x = worldVertPos.x;
				m_verts[startIndex + i].position.y = worldVertPos.y;
				m_verts[startIndex + i].color = color;
			}

			m_indices.reserve(m_indices.size() + numberOfVerts * 2);
			for (unsigned int i = 0; i < numberOfVerts - 1; i++) {
				m_indices.push_back(startIndex + i);
				m_indices.push_back(startIndex + i + 1);
			}
			m_indices.push_back(startIndex + numberOfVerts - 1);
			m_indices.push_back(startIndex);
			break;
		}
	}
}

void PhysicsRenderer::render() {
	glLineWidth(m_lineWidth);
	glBindVertexArray(m_vao);
	glDrawElements(GL_LINES, m_numElements, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void PhysicsRenderer::end() {

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_verts.size() * sizeof(DebugVertex), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_verts.size() * sizeof(DebugVertex), m_verts.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_indices.size() * sizeof(GLuint), m_indices.data());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	m_numElements = m_indices.size();
	m_indices.clear();
	m_verts.clear();
	m_program.unuse();

}

void PhysicsRenderer::dispose() {
	if (m_vao) { glDeleteVertexArrays(1, &m_vao); }
	if (m_vbo) { glDeleteBuffers(1, &m_vbo); }
	if (m_ibo) { glDeleteBuffers(1, &m_ibo); }
	m_program.dispose();
}
