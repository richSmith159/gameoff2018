#include "GLSLProgram.h"
#include <vector>
#include "TempestErrors.h"



namespace Tempest {


	GLSLProgram::GLSLProgram() {
		// empty
	}


	GLSLProgram::~GLSLProgram() {
		// empty
	}

	void GLSLProgram::init() { m_programID = glCreateProgram(); }

	void GLSLProgram::linkShaders(GLuint vertexShaderID, GLuint fragmentShaderID) {

		// attach the shaders to the program
		glAttachShader(m_programID, vertexShaderID);
		glAttachShader(m_programID, fragmentShaderID);

		// link the program and check success
		glLinkProgram(m_programID);

		GLint linkSuccess = 0;
		glGetProgramiv(m_programID, GL_LINK_STATUS, (int *)&linkSuccess);

		if (linkSuccess == GL_FALSE) {

			GLint maxLength = 0;
			glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

			// get the error log
			std::vector<char> errorLog(maxLength);
			glGetProgramInfoLog(m_programID, maxLength, &maxLength, &errorLog[0]);

			// delete the program
			glDeleteProgram(m_programID);

			// delete shaders if link was unsuccessfull
			glDeleteShader(vertexShaderID);
			glDeleteShader(fragmentShaderID);

			//print the error log and quit
			std::printf("%s\n", &(errorLog[0]));
			fatalError("Shaders failed to link!");
		}

		// if linking was successful, detach the shaders
		glDetachShader(m_programID, vertexShaderID);
		glDetachShader(m_programID, fragmentShaderID);
		glDeleteShader(fragmentShaderID);
		glDeleteShader(vertexShaderID);
	}

	void GLSLProgram::bindAttribute(const std::string & attributeName) {

		// bind the attribute and increment the number of attributes
		glBindAttribLocation(m_programID, m_numberOfAttributes++, attributeName.c_str());

	}

	GLint GLSLProgram::getUniformLocation(const std::string & uniformName) {

		// attempt to find the loction of the specified uniform
		GLint location = glGetUniformLocation(m_programID, uniformName.c_str());

		// check the uniform was found in the shader and return if successful
		if (location == GL_INVALID_INDEX) {
			fatalError("Could not find location of uniform: " + uniformName);
		}
		else {
			return location;
		}
		
	}

	void GLSLProgram::use() {

		glUseProgram(m_programID);

		for (int i = 0; i < m_numberOfAttributes; i++) {
			glEnableVertexAttribArray(i);
		}

	}

	void GLSLProgram::unuse() {

		glUseProgram(0);

		// disable each of the attributes
		for (int i = 0; i < m_numberOfAttributes; i++) {
			glDisableVertexAttribArray(i);
		}

	}

	void GLSLProgram::dispose() {
		// TODO: Implement
	}

}
