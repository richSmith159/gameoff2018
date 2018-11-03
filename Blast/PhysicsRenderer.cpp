#include "PhysicsRenderer.h"


const char* VERTEX_SHADER_SOURCE = R"(
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

const char* FRAGMENT_SHADER_SOURCE = R"(
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
	m_vertexShader.compile(VERTEX_SHADER_SOURCE);
	m_fragmentShader.compile(FRAGMENT_SHADER_SOURCE);

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
