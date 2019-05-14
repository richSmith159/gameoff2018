#include "Fractal.h"
#include <cstddef>
#include <gl\glew.h>



Fractal::Fractal() {
	// emtpy
}


Fractal::~Fractal() {
	// emtpy
}

void Fractal::init(double width, double height, double centerX, double centerY, double zoom, int iterations) {
	float verts[] = {
		-1.0f * (float)width,  1.0f * (float)height,  0.0f,
		-1.0f * (float)width,  -1.0f * (float)height,  0.0f,
		1.0f * (float)width,  -1.0f * (float)height,  0.0f,

		-1.0f * (float)width,  1.0f * (float)height,  0.0f,
		1.0f * (float)width,  -1.0f * (float)height,  0.0f,
		1.0f * (float)width,  1.0f * (float)height,  0.0f,
	};
	m_width = width;
	m_height = height;
	m_centerX = centerX;
	m_centerY = centerY;
	m_zoom = zoom;
	m_iterations = iterations;

	glGenBuffers(1, &m_vboID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glBufferData(GL_ARRAY_BUFFER, 2 * 9 * sizeof(float), verts, GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_vaoID);
	glBindVertexArray(m_vaoID);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vaoID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

}
