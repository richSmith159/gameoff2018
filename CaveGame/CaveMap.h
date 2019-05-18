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
			CELL_WIDTH,
			CELL_WIDTH
		);
	}
};

class CaveMap
{
public:
	CaveMap();
	~CaveMap();

	void init(int width, int height, int fillRate);
	inline int getWidth() { return m_width; }
	inline int getHeight() { return m_height; }
	inline Cell* getCells() { return m_cells; }
	Cell* getCell(int i, int j);
	Cell* getCell(int i);
	inline int getTotalCells() { return m_totalCells; }

private:
	int m_width;
	int m_height;
	int m_fillRate;
	int m_totalCells;
	Cell* m_cells;
};

