#include "EntityRenderer.h"

#include <iostream>


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

// output color
out vec4 color;

uniform sampler2D textureSampler;

void main() {
    
    vec4 textureColor = texture(textureSampler, fragmentUV);
    color = fragmentColor * textureColor;
}
)";


EntityRenderer::EntityRenderer() {
	// empty
}


EntityRenderer::~EntityRenderer() {
	// empty
}

void EntityRenderer::init() {
	// init the shader program and spritebatch
	m_program.init();
	m_spriteBatch.init();

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

void EntityRenderer::begin(Tempest::Camera2D * activeCamera) {

	// use the program and set the texture uniform location
	m_program.use();
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glActiveTexture(GL_TEXTURE0);

	GLint textureUniform = m_program.getUniformLocation("textureSampler");
	glUniform1i(textureUniform, 0);

	// get the camera's projection matrix (2D so orthographic)
	glm::mat4 projectionMatrix = activeCamera->getCameraMatrix();
	GLint pUniform = m_program.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	// start using the spritebatch for drawing entities
	m_spriteBatch.begin();
}

void EntityRenderer::render(Entity * entity) {
	m_spriteBatch.draw(
		entity->calculateDestRect(),
		entity->getUVRect(),
		entity->getTextureId(),
		1.0f,
		entity->getColor(),
		entity->getDirection()
	);
}

void EntityRenderer::render(Player * player) {
	m_spriteBatch.draw(
		player->calculateDestRect(),
		player->getUVRect(),
		player->getTextureId(),
		1.0f,
		player->getColor(),
		player->getDirection()
	);
}

void EntityRenderer::render(EnemySquare * enemy) {
	m_spriteBatch.draw(
		enemy->calculateDestRect(),
		enemy->getUVRect(),
		enemy->getTextureId(),
		1.0f,
		enemy->getColor(),
		enemy->getDirection()
	);
}

void EntityRenderer::render(Bullet * bullet) {
	m_spriteBatch.draw(
		bullet->calculateDestRect(),
		bullet->getUVRect(),
		bullet->getTextureId(),
		1.0f,
		bullet->getColor(),
		bullet->getDirection()
	);
}

void EntityRenderer::end() {
	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_program.unuse();

	// Reset to regular alpha blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(true);

}
