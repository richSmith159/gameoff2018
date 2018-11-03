#include <cstddef>
#include "Sprite.h"
#include "GLObjects.h"
#include "ResourceManager.h"

namespace Tempest {

	Sprite::Sprite() {
		m_vboID = 0;
	}

	Sprite::~Sprite() {

		// if the vertex buffer has been used
		// delete it when the sprite is destroyed
		if (m_vboID != 0) {
			glDeleteBuffers(1, &m_vboID);
		}

	}

	void Sprite::init(float xPos, float yPos, float width, float height, std::string texturePath) {
		m_xPos = xPos;
		m_yPos = yPos;
		m_width = width;
		m_height = height;

		// get the texture for the sprite using the resource manager
		m_texture = ResourceManager::getTexture(texturePath);

		// check if the vbo has been created
		// if it hasnt (equal to 0), then create it
		if (m_vboID == 0) {

			// get the reference of _vboID
			// change it to the ID created by genBuffers()
			glGenBuffers(1, &m_vboID);

		}

		// create array to store vertex data
		// sprite made up of 1 quad (rectangle)
		// consists of two triangles
		glVertex2D vertexData[6];

		// create first triangle

		vertexData[0].setPosition(xPos + width, yPos + height);
		vertexData[0].setUV(1.0f, 1.0f);

		vertexData[1].setPosition(xPos, yPos + height);
		vertexData[1].setUV(0.0f, 1.0f);

		vertexData[2].setPosition(xPos, yPos);
		vertexData[2].setUV(0.0f, 0.0f);

		// second triangle
		vertexData[3].setPosition(xPos, yPos);
		vertexData[3].setUV(0.0f, 0.0f);

		vertexData[4].setPosition(xPos + width, yPos);
		vertexData[4].setUV(1.0f, 0.0f);

		vertexData[5].setPosition(xPos + width, yPos + height);
		vertexData[5].setUV(1.0f, 1.0f);

		// set vertex colors
		for (int i = 0; i < 6; i++) {
			vertexData[i].setColor(255, 255, 255, 255);
		}

		// bind the buffers
		glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	void Sprite::draw() {

		// bind texture
		glBindTexture(GL_TEXTURE_2D, m_texture.id);

		// bind buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

		// give the buffer attributes (position, color, etc)
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		// position attrib pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glVertex2D), (void*)offsetof(glVertex2D, position));
		// color attrib pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(glVertex2D), (void*)offsetof(glVertex2D, color));
		// UV attrib pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glVertex2D), (void*)offsetof(glVertex2D, uv));

		// draw 6 vertices to the screen
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// tidy up
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}