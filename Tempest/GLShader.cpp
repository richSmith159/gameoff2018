#include "GLShader.h"
#include "TempestErrors.h"
#include <vector>


namespace Tempest {

	GLShader::GLShader() {
		// empty
	}


	GLShader::~GLShader() {
		// empty
	}

	void GLShader::init(ShaderType shaderType) {

		m_shaderType = shaderType;

		switch (m_shaderType) {
		case ShaderType::VERTEX:

			m_shaderID = glCreateShader(GL_VERTEX_SHADER);

			if (m_shaderID == 0) {
				fatalError("Vertex shader could not be created.");
			}
			break;

		case ShaderType::FRAGMENT:
			
			m_shaderID = glCreateShader(GL_FRAGMENT_SHADER);

			if (m_shaderID == 0) {
				fatalError("Fragment shader could not be created.");
			}

			break;

		}

	}

	void GLShader::compile(const char * shaderSource) {

		// check the shader was initialised correctly
		if (m_shaderID == 0) {
			fatalError("Shader was not initialised correctly. Was init() called?");
		}

		// use source to generate a shader
		glShaderSource(m_shaderID, 1, &shaderSource, nullptr);

		// compile the shader and check success
		glCompileShader(m_shaderID);

		GLint compilationSuccess = 0;
		glGetShaderiv(m_shaderID, GL_COMPILE_STATUS, &compilationSuccess);

		// if unsuccessful compilation, handle the error
		if (compilationSuccess == GL_FALSE) {

			GLint maxLength = 0;
			glGetShaderiv(m_shaderID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(m_shaderID, maxLength, &maxLength, &errorLog[0]);

			//Don't leak the shader
			glDeleteShader(m_shaderID);

			//Print error log and quit
			std::printf("%s\n", &(errorLog[0]));
			fatalError("Shader failed to compile");

		}

	}

}
