#include "SpriteBatch.h"
#include <algorithm>
#include "GLObjects.h"

namespace Tempest {

	Glyph::Glyph(
		const glm::vec4& destRect,
		const glm::vec4& uvRect,
		GLuint Texture,
		float Depth,
		const ColorRGBA8& color
	) : texture(Texture), depth(Depth) {
		
		// properties of glyph
		texture = Texture;
		depth = Depth;

		// set properties of each vertex for the glyph
		topLeft.color = color;
		topLeft.setPosition(destRect.x, destRect.y + destRect.w);
		topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		bottomLeft.color = color;
		bottomLeft.setPosition(destRect.x, destRect.y);
		bottomLeft.setUV(uvRect.x, uvRect.y);

		bottomRight.color = color;
		bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
		bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		topRight.color = color;
		topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
		topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

	}

	Glyph::Glyph(
		const glm::vec4& destRect,
		const glm::vec4& uvRect,
		GLuint Texture,
		float Depth,
		const ColorRGBA8& color,
		float radianAngle
	) : texture(Texture), depth(Depth) {

		texture = Texture;
		depth = Depth;

		// define vectors for 4 verts centered at origin ready for rotation calc
		glm::vec2 centerOffset(destRect.z/2, destRect.w/2);
		glm::vec2 topLeftCentered(-centerOffset.x, centerOffset.y);
		glm::vec2 bottomLeftCentered(-centerOffset.x, -centerOffset.y);
		glm::vec2 bottomRightCentered(centerOffset.x, -centerOffset.y);
		glm::vec2 topRightCentered(centerOffset.x, centerOffset.y);

		
		// perform rotation
		topLeftCentered = rotatePoint(topLeftCentered, radianAngle) + centerOffset;
		bottomLeftCentered = rotatePoint(bottomLeftCentered, radianAngle) + centerOffset;
		bottomRightCentered = rotatePoint(bottomRightCentered, radianAngle) + centerOffset;
		topRightCentered = rotatePoint(topRightCentered, radianAngle) + centerOffset;


		topLeft.color = color;
		topLeft.setPosition(destRect.x + topLeftCentered.x, destRect.y + topLeftCentered.y);
		topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);


		bottomLeft.color = color;
		bottomLeft.setPosition(destRect.x + bottomLeftCentered.x, destRect.y + bottomLeftCentered.y);
		bottomLeft.setUV(uvRect.x, uvRect.y);


		bottomRight.color = color;
		bottomRight.setPosition(destRect.x + bottomRightCentered.x, destRect.y + bottomRightCentered.y);
		bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);


		topRight.color = color;
		topRight.setPosition(destRect.x + topRightCentered.x, destRect.y + topRightCentered.y);
		topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

	}

	glm::vec2 Glyph::rotatePoint(glm::vec2 point, float radianAngle) {

		glm::vec2 rotatedVector;
		rotatedVector.x = point.x * cos(radianAngle) - point.y * sin(radianAngle);
		rotatedVector.y = point.x * sin(radianAngle) + point.y * cos(radianAngle);

		return rotatedVector;

	}

	SpriteBatch::SpriteBatch() : m_vboID(0), m_vaoID(0) {
		// empty
	}


	SpriteBatch::~SpriteBatch() {
		// empty
	}

	// init class
	void SpriteBatch::init() {
		createVertexArray();
	}

	// get everything ready to draw
	void SpriteBatch::begin(GlyphSortType sortType) {
		
		// set sort type for sorting glyphs to make batches
		m_sortType = sortType;

		// changes size of vectors back to 0
		// dont delete so memory still allocated (speed improvement)
		m_renderBatches.clear();
		m_glyphs.clear();

	}

	// add all required sprites to vector of glyphs
	// this vector will be sorted into batches
	void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color) {
		
		// add to vector of glyph objects
		// (emplace back will instantiate class when adding to vector
		m_glyphs.emplace_back(destRect, uvRect, texture, depth, color);

	}

	void SpriteBatch::draw(
		const glm::vec4& destRect,
		const glm::vec4& uvRect,
		GLuint texture,
		float depth,
		const ColorRGBA8& color,
		float radianAngle) {

		// add to vector of glyph objects with the angle
		m_glyphs.emplace_back(destRect, uvRect, texture, depth, color, radianAngle);

	}

	void SpriteBatch::draw(
		const glm::vec4& destRect,
		const glm::vec4& uvRect,
		GLuint texture,
		float depth,
		const ColorRGBA8& color,
		const glm::vec2& direction) {


		// calculate angle
		const glm::vec2 right(1.0f, 0.0f);
		float angle = acos(glm::dot(right, direction));
		if (direction.y < 0) {
			angle = -angle;
		}

		// add to vector of glyph objects with the calculated angle
		m_glyphs.emplace_back(destRect, uvRect, texture, depth, color, angle);

	}

	// function to sort the glyphs based on sort type enum class
	void SpriteBatch::sortGlyphs() {
		
		// sort based on the sort type
		switch (m_sortType) {
			case GlyphSortType::BACK_TO_FRONT:
				std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareBackToFront);
				break;

			case GlyphSortType::FRONT_TO_BACK:
				std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareFrontToBack);
				break;

			case GlyphSortType::TEXTURE:
				std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareTexture);
				break;
		}
	}

	// functions to sort vector of glyphs
	bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b) {
		return (a->depth < b->depth);
	}

	bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b) {
		return (a->depth > b->depth);
	}

	bool SpriteBatch::compareTexture(Glyph* a, Glyph* b) {
		return (a->texture < b->texture);
	}

	// postprocessing (sorting etc)
	void SpriteBatch::end() {

		// set pointers to glyphs for faster sorting...

		// resize pointer vector to correspond to any new Glyphs
		m_glyphPointers.resize(m_glyphs.size());

		// set pointers here
		for (int i = 0; i < m_glyphs.size(); i++) {
			m_glyphPointers[i] = &m_glyphs[i];
		}

		// sort glyphs into separate batches
		sortGlyphs();
		createRenderBatches();

	}

	
	void SpriteBatch::renderBatch() {
		
		// bind the array for the sprite batch
		glBindVertexArray(m_vaoID);

		// bind each texture and draw the glyphs
		for (int i = 0; i < m_renderBatches.size(); i++) {
			glBindTexture(GL_TEXTURE_2D, m_renderBatches[i].texture);
			glDrawArrays(GL_TRIANGLES, m_renderBatches[i].offset, m_renderBatches[i].numberOfVertices);
		}

		// unbind buffer
		glBindVertexArray(0);

	}

	// create batches
	void SpriteBatch::createRenderBatches() {
		
		// create vector to store verts for vbo
		std::vector<glVertex2D> vertices;

		// allocate estimated amount of memory required at start
		// increases speed as vector doesnt have to be resized
		vertices.resize(m_glyphPointers.size() * 6);
		
		// check if glyphs are present
		if (m_glyphPointers.empty()) {
			return;
		}

		// keep track of current vertex
		int currentVertex = 0;
		int offset = 0;
		
		// if no glyphs in render batches, add first one
		m_renderBatches.emplace_back(offset, 6, m_glyphPointers[0]->texture);

		// add the glyphs verts
		vertices[currentVertex++] = m_glyphPointers[0]->topLeft;
		vertices[currentVertex++] = m_glyphPointers[0]->bottomLeft;
		vertices[currentVertex++] = m_glyphPointers[0]->bottomRight;
		vertices[currentVertex++] = m_glyphPointers[0]->bottomRight;
		vertices[currentVertex++] = m_glyphPointers[0]->topRight;
		vertices[currentVertex++] = m_glyphPointers[0]->topLeft;
		
		offset += 6;

		// iterate over glyphs
		for (int currentGlyph = 1; currentGlyph < m_glyphs.size(); currentGlyph++) {
			
			// compare textures to determine if a new batch needs to be made
			if (m_glyphPointers[currentGlyph]->texture != m_glyphPointers[currentGlyph - 1]->texture) {

				m_renderBatches.emplace_back(offset, 6, m_glyphPointers[currentGlyph]->texture);

			} else {

				m_renderBatches.back().numberOfVertices += 6;

			}
			
			// add each of the glyph's verts to the vertices
			vertices[currentVertex++] = m_glyphPointers[currentGlyph]->topLeft;
			vertices[currentVertex++] = m_glyphPointers[currentGlyph]->bottomLeft;
			vertices[currentVertex++] = m_glyphPointers[currentGlyph]->bottomRight;
			vertices[currentVertex++] = m_glyphPointers[currentGlyph]->bottomRight;
			vertices[currentVertex++] = m_glyphPointers[currentGlyph]->topRight;
			vertices[currentVertex++] = m_glyphPointers[currentGlyph]->topLeft;
			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
		// orphan buffer
		// get rid of old buffer as data already exists (speed improvement)
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glVertex2D), nullptr, GL_DYNAMIC_DRAW);

		// give data to new, empty buffer
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size()*sizeof(glVertex2D), vertices.data());

		// unbind buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	void SpriteBatch::createVertexArray() {
		
		// check if vao already exists
		// (avoids memory leak)
		if (m_vaoID == 0) {
			
			// generate vertex array object
			// give id to _vaoID
			glGenVertexArrays(1, &m_vaoID);
		}

		// anything that changes opengl state gets stored in VAO
		glBindVertexArray(m_vaoID);
		
		// check if vbo already exists
		// (avoids memory leak)
		if (m_vboID == 0) {
			
			// generate vertex buffer object
			// give idto _vboID
			glGenBuffers(1, &m_vboID);
		}

		// will now automatically bind buffer
		// (will not have to call this every draw call)
		glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

		// give the buffer attributes (position, color, etc)
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		// position attrib pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glVertex2D), (void*)offsetof(glVertex2D, position));
		// color attrib pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(glVertex2D), (void*)offsetof(glVertex2D, color));
		// UV attrib pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glVertex2D), (void*)offsetof(glVertex2D, uv));

		// unbind VAO
		// handles all cleanup (e.g. disable attrib arrays/pointers)
		glBindVertexArray(0);

	}

}