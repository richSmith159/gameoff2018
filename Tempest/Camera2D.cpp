#include "Camera2D.h"


namespace Tempest {
	
	Camera2D::Camera2D() : 
		m_position(0.0f, 0.0f),
		m_cameraMatrix(1.0f),
		m_orthogonalMatrix(1.0f),
		m_matrixUpdateRequired(true),
		m_screenWidth(500),
		m_screenHeight(500) {
		// empty
	}


	Camera2D::~Camera2D() {
		// empty
	}

	void Camera2D::init(int screenWidth, int screenHeight) {

		m_screenWidth = screenWidth;
		m_screenHeight = screenHeight;
		m_orthogonalMatrix = glm::ortho(0.0f, (float)m_screenWidth, 0.0f, (float)m_screenHeight);

	}

	void Camera2D::update() {

		if (m_matrixUpdateRequired) {

			glm::vec3 translate(-m_position.x + m_screenWidth / 2, -m_position.y + m_screenHeight / 2, 0.0f);

			m_cameraMatrix = glm::translate(m_orthogonalMatrix, translate);

			glm::vec3 scale(m_scale, m_scale, 0.0f);
			m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_cameraMatrix;

			m_matrixUpdateRequired = false;

		}

	}

	glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCoords) {

		screenCoords.y = m_screenHeight - screenCoords.y;
		screenCoords -= glm::vec2(m_screenWidth / 2, m_screenHeight / 2);
		screenCoords /= m_scale;
		screenCoords += m_position;
		
		return screenCoords;

	}

}