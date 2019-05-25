#include "SimpleRenderer.h"


const char* VERTEX_SHADER_SOURCE = R"(
#version 330
//The vertex shader operates on each vertex

//input data from the VBO. Each vertex is 2 floats
in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;

out vec2 fragmentPosition;
out vec4 fragmentColor;
out vec2 fragmentUV;

uniform mat4 P;

void main() {

    // x,y position on screen
    gl_Position.xy = (P * vec4(vertexPosition, 0.0, 1.0)).xy;
    
	// 2D so no Z coord
    gl_Position.z = 0.0;
    
    // normalized coords
    gl_Position.w = 1.0;
    
    fragmentPosition = vertexPosition;
    fragmentColor = vertexColor;
    fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
}
)";


const char* FRAGMENT_SHADER_SOURCE = R"(
#version 330

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform sampler2D textureSampler;

void main() {

    vec4 textureColor = texture(textureSampler, fragmentUV);
    
    color = fragmentColor * textureColor;
}
)";


SimpleRenderer::SimpleRenderer() {
	// empty
}


SimpleRenderer::~SimpleRenderer() {
	// empty
}

void SimpleRenderer::init() {

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
	m_program.bindAttribute("vertexUV");
	m_program.linkShaders(m_vertexShader.getShaderID(), m_fragmentShader.getShaderID());
}

void SimpleRenderer::begin(Tempest::Camera2D * camera) {

	// use the program
	m_program.use();
	// glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	// init sprite batches
	m_spriteBatch.init();
	m_characterSpriteBatch.init();

	// set the texture uniform location
	glActiveTexture(GL_TEXTURE0);
	GLint textureUniform = m_program.getUniformLocation("textureSampler");
	glUniform1i(textureUniform, 0);

	// get the camera's projection matrix (2D so orthographic)
	glm::mat4 projectionMatrix = camera->getCameraMatrix();
	GLint pUniform = m_program.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

}

void SimpleRenderer::renderTile(glm::vec4 destRect, glm::vec4 uvRect, int textureID, float depth, Tempest::ColorRGBA8 color, float angle) {
	m_spriteBatch.draw(
		destRect,
		uvRect,
		textureID,
		depth,
		color,
		angle
	);
}

void SimpleRenderer::renderCharacter(glm::vec4 destRect, glm::vec4 uvRect, int textureID, float depth, Tempest::ColorRGBA8 color, glm::vec2 direction) {
	m_characterSpriteBatch.draw(
		destRect,
		uvRect,
		textureID,
		depth,
		color,
		direction
	);
}

void SimpleRenderer::end() {

	m_spriteBatch.renderBatch();
	m_characterSpriteBatch.renderBatch();
	m_program.unuse();
}
