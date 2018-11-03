#include "TextureCache.h"
#include <SOIL\SOIL.h>
#include <iostream>
#include "GLObjects.h"

namespace Tempest {

	TextureCache::TextureCache() {
		// empty
	}


	TextureCache::~TextureCache() {
		// empty
	}

	glTexture TextureCache::constructTexture(std::string filepath) {

		// create new texture object (empty at this point)
		glTexture newTexture;
		newTexture.filepath = filepath;
		// generate new texture with opengl
		glGenTextures(1, &newTexture.id);

		// use SOIL library to load raw data from image file
		std::cout << filepath.c_str() << std::endl;
		unsigned char* textureData = SOIL_load_image(filepath.c_str(), &newTexture.width, &newTexture.height, 0, SOIL_LOAD_RGBA);

		if (textureData == nullptr) {

			std::cout << "IMAGE NOT LOADED PROPERLY" << std::endl;
			std::cout << filepath << std::endl;
			std::cout << "- - - - - - - -" << std::endl;

		}
		else {

			std::cout << "IMAGE LOADED PROPERLY" << std::endl;
			std::cout << filepath << std::endl;
			std::cout << "- - - - - - - -" << std::endl;

			glEnable(GL_TEXTURE_2D);

			// bind new texture to set texture parameters
			glBindTexture(GL_TEXTURE_2D, newTexture.id);

			// send raw image data to opengl (stored in vram)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, newTexture.width, newTexture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);

			// generate mipmaps
			glGenerateMipmap(GL_TEXTURE_2D);

			// free the image data ASAP to release memory
			SOIL_free_image_data(textureData);

			// texture wrapping
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			// filters pixels based on size of size of texture
			// set linear interpolation
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

			// unbind texture
			glBindTexture(GL_TEXTURE_2D, 0);

		}

		return newTexture;

	}

	glTexture TextureCache::getTexture(std::string textureFilepath) {

		// create iterator and try to find texture by filepath
		auto mapIterator = m_textureMap.find(textureFilepath);

		// if the texture was not found in the map
		if (mapIterator == m_textureMap.end()) {
			std::cout << "Texture not found in cache...adding now." << std::endl;
			
			// create a new texture object
			glTexture newTexture = constructTexture(textureFilepath);

			// insert new texture into texture map
			std::pair<std::string, glTexture> newPair(textureFilepath, newTexture);
			m_textureMap.insert(newPair);

			// return new texture
			return newTexture;

		}
		std::cout << "Texture found in cache...returning." << std::endl;
		// if the texture was found, return it
		return mapIterator->second;

	}

}