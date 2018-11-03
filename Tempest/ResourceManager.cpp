#include "ResourceManager.h"

namespace Tempest {

	TextureCache ResourceManager::m_textureCache;

	glTexture ResourceManager::getTexture(const std::string& textureFilepath) {
		return m_textureCache.getTexture(textureFilepath);
	}

}