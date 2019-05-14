#pragma once

#include <glm\glm\glm.hpp>
#include <GL\glew.h>

class Fractal
{
public:
	Fractal();
	~Fractal();

	void setWidth(double newWidth) { m_width = newWidth; }
	void setHeight(double newHeight) { m_height = newHeight; }
	void setCenterX(double centerX) { m_centerX = centerX; }
	void setCenterY(double centerY) { m_centerY = centerY; }
	void setZoom(double zoom) { m_zoom = zoom; }
	void setIterations(int iterations) { m_iterations = iterations; }
	void setRed(float newRed) { m_red = newRed; }
	void setGreen(float newGreen) { m_green = newGreen; }
	void setBlue(float newBlue) { m_blue = newBlue; }

	double getWidth() { return m_width; }
	double getHeight() { return m_height; }
	double getCenterX() { return m_centerX; }
	double getCenterY() { return m_centerY; }
	double getZoom() { return m_zoom; }
	glm::vec3 getRGB() { return glm::vec3(m_red, m_green, m_blue); }
	int getIterations() { return m_iterations; }

	void offsetZoom(double offset) { m_zoom += offset; }
	void offsetIterations(double offset) { m_iterations += offset; }
	void offsetCenterX(double offset) { m_centerX += offset; }
	void offsetCenterY(double offset) { m_centerY += offset; }

	void init(
		double width,
		double height,
		double centerX,
		double centerY,
		double zoom,
		int iterations
	);

private:
	GLuint m_vboID;
	GLuint m_vaoID;
	double m_width;
	double m_height;
	double m_centerX;
	double m_centerY;
	double m_zoom;
	float m_red = 9.0f;
	float m_green = 15.0f;
	float m_blue = 8.5f;
	int m_iterations;

};

