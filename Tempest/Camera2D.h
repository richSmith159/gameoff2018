#pragma once

#include <glm\glm\glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>

namespace Tempest {

	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void init(int screenWidth, int screenHeight);

		void update();

		glm::vec2 convertScreenToWorld(glm::vec2 screenCoords);


		void setPosition(const glm::vec2& newPosition) { m_position = newPosition; m_matrixUpdateRequired = true; }
		void setScale(const float& newScale) { m_scale = newScale; m_matrixUpdateRequired = true; }
		void offsetPosition(const glm::vec2& positionOffset) { m_position += positionOffset; m_matrixUpdateRequired = true; }
		void offsetScale(const float& scaleOffset) { m_scale += scaleOffset; m_matrixUpdateRequired = true; }

		glm::vec2 getPosition() { return m_position; }
		float getScale() { return m_scale; }
		glm::mat4 getCameraMatrix() { return m_cameraMatrix; }
		float getAspectRatio() { return (float)m_screenWidth / (float)m_screenHeight; }


	private:


		int m_screenWidth, m_screenHeight;
		bool m_matrixUpdateRequired;
		float m_scale;
		glm::vec2 m_position;
		glm::mat4 m_cameraMatrix;
		glm::mat4 m_orthogonalMatrix;


	};

}