#pragma once

#include <Tempest\GLObjects.h>
#include <glm\glm\glm.hpp>
#include <Tempest\ResourceManager.h>
#include <map>

const int CELL_WIDTH = 8;

enum class CellType { ROCK, EMPTY, EXTRACTION };

struct Cell {
	CellType cellType;
	glm::vec2 position;
	Tempest::glTexture texture;
	Tempest::ColorRGBA8 color = Tempest::ColorRGBA8(255, 255, 255, 255);
	glm::vec2 tileCoords;

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

	void init(int width, int height, int fillRate, int numCharacters);
	inline int getWidth() { return m_width; }
	inline int getHeight() { return m_height; }
	inline Cell* getCells() { return m_cells; }
	Cell* getCell(int i, int j);
	Cell* getCell(int i);
	inline int getTotalCells() { return m_totalCells; }
	void smoothMap(const int& smoothingRadius);
private:
	int countCellNeighboursOfType(const glm::vec2& tileCoords, CellType cellType, const int& radius);
	void setBoundaries(const int& boundaryRadius, CellType boundaryType);
	void populateTextureMap();
	void setInitialExtractionPoint(int size);
	Tempest::glTexture getTextureForCellType(CellType cellType);

	int m_width;
	int m_height;
	int m_fillRate;
	int m_totalCells;
	int m_smoothingIterations = 5;
	Cell* m_cells;

	std::map<CellType, Tempest::glTexture> m_cellTypeTextureMap;

};
