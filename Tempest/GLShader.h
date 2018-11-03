#pragma once

#include <GL\glew.h>

namespace Tempest {

	enum class ShaderType {
		VERTEX,
		FRAGMENT
	};

	class GLShader
	{
	public:
		GLShader();
		~GLShader();

		void init(ShaderType shaderType);

		void compile(const char* shaderSource);

		GLuint getShaderID() { return m_shaderID; }

		ShaderType getShaderType() { return m_shaderType; }

	private:

		GLuint m_shaderID;
		ShaderType m_shaderType;

	};

}

