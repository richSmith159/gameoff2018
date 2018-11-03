#pragma once

#include <GL\glew.h>
#include <string>

namespace Tempest {

	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();
		
		// create the opengl program ID
		void init();

		// links the fragment and vertex shaders to the program
		// opengl program and both shaders must have ID's before calling function
		// shaders must have compiled source
		void linkShaders(GLuint vertexShaderID, GLuint fragmentShaderID);

		// binds attribute into the shader program
		void bindAttribute(const std::string& attributeName);
		
		// get the location of a uniform in the shader
		// will call fatalError() if not found
		GLint getUniformLocation(const std::string& uniformName);
		
		// enable program and add attributes
		void use();
		
		// disable program and attributes
		void unuse();
		
		// delete the program
		void dispose();

		// getters
		GLuint getProgramID() { return m_programID; }

	private:

		GLuint m_programID;
		int m_numberOfAttributes;

	};


}


