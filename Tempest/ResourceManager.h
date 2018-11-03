#pragma once
#include "GLObjects.h"
#include "TextureCache.h"
#include <string>

namespace Tempest {

	class ResourceManager
	{
	public:
		
		static glTexture getTexture(const std::string& textureFilepath);

	private:

		static TextureCache m_textureCache;

	};

}