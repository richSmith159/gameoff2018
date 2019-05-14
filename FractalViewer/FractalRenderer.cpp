#include "FractalRenderer.h"

#include <Tempest\GLObjects.h>

const char* VERTEX_SHADER_SOURCE = R"(
#version 450
in vec2 vertexPosition;

out vec2 fragmentPosition;

uniform mat4 P;

void main() {

    // x,y position on screen
    gl_Position.xy = (P * vec4(vertexPosition, 0.0, 1.0)).xy;
    
	// 2D so no Z coord
    gl_Position.z = 0.0;
    
    // normalized coords
    gl_Position.w = 1.0;
    
    fragmentPosition = vertexPosition;
}
)";

const char* FRAGMENT_SHADER_SOURCE = R"(
#version 450

out vec4 colorOut;
uniform double screen_ratio;
uniform dvec2 screen_size;
uniform dvec2 center;
uniform double zoom;
uniform float red_in;
uniform float green_in;
uniform float blue_in;
uniform float time;
uniform int iterations;


vec4 calculateColor(float t, float red, float green, float blue) {
    float r = red * (1.0 - t) * t * t * t;
    float g = green * (1.0 - t) * (1.0 - t) * t * t;
    float b = blue * (1.0 - t) * (1.0 - t) * (1.0 - t) * t;
    return vec4(r, g, b, 1.0);
}

void main() {
	
	dvec2 z, c;
    c.x = screen_ratio * (gl_FragCoord.x / screen_size.x - 0.5);
    c.y = (gl_FragCoord.y / screen_size.y - 0.5);

    c.x /= zoom;
    c.y /= zoom;

    c.x += center.x;
    c.y += center.y;

    int i;
    for(i = 0; i < iterations; i++) {
        double x = (z.x * z.x - z.y * z.y) + c.x;
		double y = (z.y * z.x + z.x * z.y) + c.y;

		if((x * x + y * y) > 2.0) break;
		z.x = x;
		z.y = y;
    }

    double t = double(i) / double(iterations);

    colorOut = calculateColor(float(t), red_in, green_in, blue_in);
}

)";

FractalRenderer::FractalRenderer() {
	// empty
}


FractalRenderer::~FractalRenderer() {
	// empty
}



void FractalRenderer::init() {
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
	m_program.linkShaders(m_vertexShader.getShaderID(), m_fragmentShader.getShaderID());

}

void FractalRenderer::begin(Tempest::Camera2D * activeCamera) {

	// use the program and set the texture uniform location
	m_program.use();
	// glDepthMask(GL_FALSE);

	// get the camera's projection matrix (2D so orthographic)
	glm::mat4 projectionMatrix = activeCamera->getCameraMatrix();
	GLint pUniform = m_program.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	// start using the spritebatch for drawing entities
	m_spriteBatch.begin();
}

void FractalRenderer::render(Fractal* fractal) {
	glUniform2d(glGetUniformLocation(m_program.getProgramID(), "screen_size"), fractal->getWidth(), fractal->getHeight());
	glUniform1d(glGetUniformLocation(m_program.getProgramID(), "screen_ratio"), fractal->getWidth() / fractal->getHeight());
	glUniform2d(glGetUniformLocation(m_program.getProgramID(), "center"), fractal->getCenterX(), fractal->getCenterY());
	glUniform1d(glGetUniformLocation(m_program.getProgramID(), "zoom"), fractal->getZoom());
	glUniform1i(glGetUniformLocation(m_program.getProgramID(), "iterations"), fractal->getIterations());
	glUniform1f(glGetUniformLocation(m_program.getProgramID(), "red_in"), fractal->getRGB().x);
	glUniform1f(glGetUniformLocation(m_program.getProgramID(), "green_in"), fractal->getRGB().y);
	glUniform1f(glGetUniformLocation(m_program.getProgramID(), "blue_in"), fractal->getRGB().z);
}

void FractalRenderer::end() {

	glDrawArrays(GL_TRIANGLES, 0, 6);

	m_program.unuse();
}
