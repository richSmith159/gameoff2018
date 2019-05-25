#pragma once

#include <Tempest\Camera2D.h>
#include <Tempest\GLSLProgram.h>
#include <Tempest\GLShader.h>
#include <Tempest\SpriteBatch.h>


class SimpleRenderer
{
public:
	SimpleRenderer();
	~SimpleRenderer();

	void init();
	void begin(Tempest::Camera2D* camera);
	void beginTileSpriteBatch() { m_spriteBatch.begin(Tempest::GlyphSortType::BACK_TO_FRONT); }
	void endTileSpriteBatch() { m_spriteBatch.end(); };
	void beginCharacterSpriteBatch() { m_characterSpriteBatch.begin(Tempest::GlyphSortType::BACK_TO_FRONT); };
	void endCharacterSpriteBatch() { m_characterSpriteBatch.end(); };
	void renderTile(glm::vec4 destRect, glm::vec4 uvRect, int textureID, float depth, Tempest::ColorRGBA8 color, float angle);
	void renderCharacter(glm::vec4 destRect, glm::vec4 uvRect, int textureID, float depth, Tempest::ColorRGBA8 color, glm::vec2 direction);
	void end();

private:
	Tempest::SpriteBatch m_spriteBatch;
	Tempest::SpriteBatch m_characterSpriteBatch;
	Tempest::GLShader m_vertexShader;
	Tempest::GLShader m_fragmentShader;
	Tempest::GLSLProgram m_program;
};

