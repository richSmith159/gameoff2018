#pragma once

#include <map>
#include "GLObjects.h"

namespace Tempest {

	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();
		
		// fetch texture from cache or load from file if needed
		glTexture getTexture(std::string textureFilepath);

	private:

		// load texture from file and construct glTexture struct
		glTexture constructTexture(std::string filepath);

		// map to store textures
		// associates filepath to glTexture
		std::map<std::string, glTexture> m_textureMap;

	};

}