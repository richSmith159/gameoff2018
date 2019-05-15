#include "CaveMap.h"

#include <random>



CaveMap::CaveMap() {
	// emtpy
}


CaveMap::~CaveMap() {
	// emtpy
}

void CaveMap::init(int width, int height, int fillRate) {
	m_width = width;
	m_height = height;
	m_fillRate = fillRate;

	Tempest::ColorRGBA8 rockColor = Tempest::ColorRGBA8(130, 63, 1, 255);
	Tempest::ColorRGBA8 emptyColor = Tempest::ColorRGBA8(237, 233, 230, 255);

	std::random_device rd;
	std::mt19937 randGenerator(rd());
	std::uniform_real_distribution<float> randomNumber(0, 100);
	m_cells = new Cell*[width];

	for (int i = 0; i < width; i++) {
		m_cells[i] = new Cell[height];
		for (int j = 0; j < height; j++) {
			bool filled = randomNumber(randGenerator) < m_fillRate;
			Cell newCell;
			newCell.position = glm::vec2(i * CELL_WIDTH, j * CELL_WIDTH);
			newCell.cellType = filled ? CellType::ROCK : CellType::EMPTY;
			newCell.color = filled ? rockColor : emptyColor;
			m_cells[i][j] = newCell;
		}
	}
}
