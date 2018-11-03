#pragma once
#include <GL\glew.h>
#include <glm\glm\glm.hpp>
#include "glObjects.h"
#include <vector>

namespace Tempest {
	
	// enum classes to determine sorting of glyphs
	enum class GlyphSortType {
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	// hold vertices, texture and depth for single sprite
	class Glyph {
	
	public:
		Glyph();
		Glyph(
			const glm::vec4& destRect,
			const glm::vec4& uvRect,
			GLuint Texture,
			float Depth,
			const ColorRGBA8& color
		);

		Glyph(
			const glm::vec4& destRect,
			const glm::vec4& uvRect,
			GLuint Texture,
			float Depth,
			const ColorRGBA8& color,
			float radianAngle
		);

		// id of texture
		GLuint texture;

		// z depth
		float depth;

		// vertices for the glyph
		glVertex2D topLeft;
		glVertex2D bottomLeft;
		glVertex2D topRight;
		glVertex2D bottomRight;

	private:

		// function to rotate point around an angle
		glm::vec2 rotatePoint(glm::vec2 point, float radianAngle);

	};

	// class to store offset of each render batch
	// offset applies to data in VBO
	// allows all batches of different textures to be found in VBO
	// means only one VBO is needed to draw all textures
	class RenderBatch {

	public:
		
		RenderBatch(GLuint Offset, GLuint numVerts, GLuint tex) :
			offset(Offset),
			numberOfVertices(numVerts),
			texture(tex) {
		}

		GLuint offset;
		GLuint numberOfVertices;
		GLuint texture;

	};



	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		// init class
		void init();

		// get everything ready to draw
		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		
		// add all required sprites to batch

		// overload draw functions to allow for rotations...

		// draw with no rotation
		void draw(
			const glm::vec4& destRect,
			const glm::vec4& uvRect,
			GLuint texture,
			float depth,
			const ColorRGBA8& color
		);

		// draw with an angle
		void draw(
			const glm::vec4& destRect,
			const glm::vec4& uvRect,
			GLuint texture,
			float depth,
			const ColorRGBA8& color,
			float radianAngle
		);

		// draw with a direction
		void draw(
			const glm::vec4& destRect,
			const glm::vec4& uvRect,
			GLuint texture,
			float depth,
			const ColorRGBA8& color,
			const glm::vec2& direction
		);
		
		// postprocessing (sorting etc)
		void end();

		// draw to screen
		void renderBatch();


	private:

		void createRenderBatches();
		void createVertexArray();
		void sortGlyphs();

		// sorting functionas
		static bool compareFrontToBack(Glyph* a, Glyph* b);
		static bool compareBackToFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

		// vertex buffer object ID
		GLuint m_vboID;

		// vertex array object ID
		GLuint m_vaoID;
		
		// use two vectors for glyphs
		// vector of glyph pointers for sorting
		// vector of glyph objects to store actual glyphs
		std::vector<Glyph> m_glyphs;
		std::vector<Glyph*> m_glyphPointers;
		std::vector<RenderBatch> m_renderBatches;

		// method of sorting glyphs
		GlyphSortType m_sortType;

	};

}