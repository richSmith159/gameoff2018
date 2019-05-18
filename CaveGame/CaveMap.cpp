#include "CaveMap.h"
#include <Tempest\ResourceManager.h>
#include <random>
#include <iostream>



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
	m_totalCells = width * height;
	m_cells = new Cell[m_totalCells];

	Tempest::ColorRGBA8 rockColor = Tempest::ColorRGBA8(130, 63, 1, 255);
	Tempest::ColorRGBA8 emptyColor = Tempest::ColorRGBA8(237, 233, 230, 255);
	Tempest::glTexture rockTexture = Tempest::ResourceManager::getTexture("Textures/rock_1.jpg");
	Tempest::glTexture emptyTexture = Tempest::ResourceManager::getTexture("Textures/empty_1.jpg");

	std::random_device rd;
	std::mt19937 randGenerator(rd());
	std::uniform_real_distribution<float> randomNumber(0, 100);
	
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {

			// new blank cell
			Cell newCell;
			
			// calc index in map and if filled
			int index = i + (j * width);
			bool filled = randomNumber(randGenerator) < m_fillRate;
			
			// init cell values
			newCell.position = glm::vec2(i * CELL_WIDTH, j * CELL_WIDTH);
			glm::vec4 destRect = newCell.calculateDestRect();
			std::cout << "i: " << i << " j: " << j << " posX: " << newCell.position.x << " posY: " << newCell.position.y << " drX: " << destRect.x << " drY: " << destRect.y << " drx: " << destRect.z << " drW: " << destRect.w << std::endl;
			newCell.cellType = filled ? CellType::ROCK : CellType::EMPTY;
			newCell.texture = filled ? rockTexture : emptyTexture;
			newCell.color = filled ? rockColor : emptyColor;
			m_cells[index] = newCell;
		}
	}
}

Cell * CaveMap::getCell(int i, int j) {
	return &m_cells[i + j * m_width];
}

Cell * CaveMap::getCell(int i) {
	return &m_cells[i];
}
