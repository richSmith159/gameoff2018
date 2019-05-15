#pragma once

#include <Tempest\GLObjects.h>
#include <glm\glm\glm.hpp>


const int CELL_WIDTH = 8;

enum class CellType { ROCK, EMPTY };

struct Cell {
	CellType cellType;
	glm::vec2 position;
	Tempest::glTexture texture;
	Tempest::ColorRGBA8 color;

	glm::vec4 calculateDestRect() {
		return glm::vec4(
			position.x,
			position.y,
			position.x + CELL_WIDTH,
			position.y + CELL_WIDTH
		);
	}
};

class CaveMap
{
public:
	CaveMap();
	~CaveMap();

	void init(int width, int height, int fillRate);

private:
	int m_width;
	int m_height;
	int m_fillRate;
	Cell** m_cells;
};

