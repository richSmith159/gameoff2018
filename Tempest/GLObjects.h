#pragma once
#include <GL/glew.h>
#include <glm/glm/glm.hpp>
#include <string>

#define DEFAULT_NUM_BONES_PER_VERTEX 4

namespace Tempest {

	struct Position {
		float x;
		float y;
	};

	struct ColorRGBA8 {
		ColorRGBA8() : r(0), g(0), b(0), a(0) {}
		ColorRGBA8(GLubyte R, GLubyte G, GLubyte B, GLubyte A) :
			r(R), g(G), b(B), a(A) { }

		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;

	};

	struct UV {
		float u;
		float v;
	};
	
	struct glVertex2D {
		
		Position position;
		ColorRGBA8 color;
		UV uv;

		void setPosition(float x, float y) {
			position.x = x;
			position.y = y;
		}

		void setPosition(glm::vec2 newPosition) {
			position.x = newPosition.x;
			position.y = newPosition.y;
		}

		void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}

		void setUV(float u, float v) {
			uv.u = u;
			uv.v = v;
		}

		void setUV(glm::vec2 newUV) {
			uv.u = newUV.x;
			uv.v = newUV.y;
		}

	};

	struct glTexture {
		std::string filepath;
		int width, height;
		GLuint id;
	};


	struct glMaterial {
		std::string name;
		glTexture* diffuse = nullptr;
		glTexture* normal = nullptr;
		glTexture* specular = nullptr;
		glTexture* emission = nullptr;
		glm::vec3 ambientColor;
		glm::vec3 diffuseColor;
		glm::vec3 specularColor;
		float specularity;
	};


	namespace LIGHTING {

		// struct containing data for a single point light
		// uses values to simulate attenuation/fall off
		struct glPointLight {

			glPointLight(
				glm::vec3 pos,
				glm::vec3 ambCol,
				glm::vec3 diffCol,
				glm::vec3 specCol,
				float constantTerm,
				float linearTerm,
				float quadraticTerm
			) : position(pos),
				ambientColor(ambCol),
				diffuseColor(diffCol),
				specularColor(specCol),
				constant(constantTerm),
				linear(linearTerm),
				quadratic(quadraticTerm) {}

			glm::vec3 position;
			glm::vec3 ambientColor;
			glm::vec3 diffuseColor;
			glm::vec3 specularColor;

			float constant;
			float linear;
			float quadratic;

		};
		
		// struct containing data for single directional lightsource
		// direcional light source does not have a position, just a direction
		// (e.g. sunlight)
		struct glDirectionalLight {

			glDirectionalLight(
				glm::vec3 dir,
				glm::vec3 amb,
				glm::vec3 diff,
				glm::vec3 spec
			) : direction(dir),
				ambient(amb),
				diffuse(diff),
				specular(spec) {}

			glm::vec3 direction;
			glm::vec3 ambient;
			glm::vec3 diffuse;
			glm::vec3 specular;

		};


	}

}
