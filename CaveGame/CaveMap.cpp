#include "CaveMap.h"
#include <random>
#include <iostream>



CaveMap::CaveMap() {
	// emtpy
}


CaveMap::~CaveMap() {
	// emtpy
}

void CaveMap::init(int width, int height, int fillRate, int numCharacters) {
	// init values
	m_width = width;
	m_height = height;
	m_fillRate = fillRate;
	m_totalCells = width * height;
	m_cells = new Cell[m_totalCells];

	// setup celltype -> texture mapping
	populateTextureMap();

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
			newCell.cellType = filled ? CellType::ROCK : CellType::EMPTY;
			newCell.texture = getTextureForCellType(newCell.cellType);
			newCell.tileCoords = glm::vec2(i, j);
			m_cells[index] = newCell;
		}
	}

	for (int i = 0; i < 5; i++) {
		smoothMap(1);
	}
	setBoundaries(1, CellType::ROCK);

	setInitialExtractionPoint(1);
}

Cell * CaveMap::getCell(int i, int j) {
	return &m_cells[i + j * m_width];
}

Cell * CaveMap::getCell(int i) {
	return &m_cells[i];
}

int CaveMap::countCellNeighboursOfType(const glm::vec2 & tileCoords, CellType cellType, const int & radius) {
	int typeCount = 0;
	for (int i = tileCoords.x - radius; i <= tileCoords.x + radius; i++) {
		for (int j = tileCoords.y - radius; j <= tileCoords.y + radius; j++) {
			if (i >= 0 && i < m_width && j >= 0 && j < m_height) {
				if (i != tileCoords.x || j != tileCoords.y) {
					if (getCell(i, j)->cellType == cellType) {
						typeCount++;
					}
				}
			}
		}
	}
	return typeCount;
}

void CaveMap::smoothMap(const int& smoothingRadius) {
	std::cout << "CALLED" << std::endl;
	for (int i = 0; i < m_totalCells; i++) {
		Cell* currentCell = getCell(i);
		
		int rockTileCount = countCellNeighboursOfType(
			currentCell->tileCoords, CellType::ROCK, smoothingRadius
		);

		if (rockTileCount > 4) {
			currentCell->cellType = CellType::ROCK;
			currentCell->texture = getTextureForCellType(CellType::ROCK);
		}
		else if (rockTileCount < 4) {
			currentCell->cellType = CellType::EMPTY;
			currentCell->texture = getTextureForCellType(CellType::EMPTY);
		}
	}
}

void CaveMap::setBoundaries(const int & boundaryRadius, CellType boundaryType) {
	for (int i = 0; i < boundaryRadius; i++) {
		for (int j = 0; j < m_height; j++) {
			Cell* cell = getCell(i, j);
			cell->cellType = boundaryType;
			cell->texture = getTextureForCellType(boundaryType);
		}
	}
	for (int i = m_width -1 ; i >= m_width - boundaryRadius; i--) {
		for (int j = 0; j < m_height; j++) {
			Cell* cell = getCell(i, j);
			cell->cellType = boundaryType;
			cell->texture = getTextureForCellType(boundaryType);
		}
	}

	for (int i = 0; i < m_width; i++) {
		for (int j = 0; j < boundaryRadius; j++) {
			Cell* cell = getCell(i, j);
			cell->cellType = boundaryType;
			cell->texture = getTextureForCellType(boundaryType);
		}
	}
	for (int i = 0; i < m_width; i++) {
		for (int j = m_height - 1; j >= m_height - boundaryRadius; j--) {
			Cell* cell = getCell(i, j);
			cell->cellType = boundaryType;
			cell->texture = getTextureForCellType(boundaryType);
		}
	}
}

void CaveMap::populateTextureMap() {
	Tempest::glTexture rockTexture = Tempest::ResourceManager::getTexture("Textures/rock_1.jpg");
	Tempest::glTexture emptyTexture = Tempest::ResourceManager::getTexture("Textures/empty_1.jpg");
	Tempest::glTexture extractionTexture = Tempest::ResourceManager::getTexture("Textures/extraction.jpg");
	m_cellTypeTextureMap.insert({CellType::ROCK, rockTexture});
	m_cellTypeTextureMap.insert({CellType::EMPTY, emptyTexture});
	m_cellTypeTextureMap.insert({CellType::EXTRACTION, extractionTexture});
}

void CaveMap::setInitialExtractionPoint(int size) {
	static const int INITIAL_X_POS = 1;
	static const int INITIAL_Y_POS = 1;

	for (int i = INITIAL_X_POS; i <= (size * 2) + 2; i++) {
		for (int j = INITIAL_Y_POS; j <= (size * 2) + 2; j++) {
			Cell* cell = getCell(i, j);
			cell->cellType = CellType::EMPTY;
			cell->texture = getTextureForCellType(CellType::EMPTY);
		}
	}

	for (int i = INITIAL_X_POS + size; i < INITIAL_X_POS + size + 2; i++) {
		for (int j = INITIAL_Y_POS + size; j < INITIAL_Y_POS + size + 2; j++) {
			Cell* cell = getCell(i, j);
			cell->cellType = CellType::EXTRACTION;
			cell->texture = getTextureForCellType(CellType::EXTRACTION);
		}
	 }

}

Tempest::glTexture CaveMap::getTextureForCellType(CellType cellType) {
	std::map<CellType, Tempest::glTexture>::iterator it;
	it = m_cellTypeTextureMap.find(cellType);
	if (it != m_cellTypeTextureMap.end()) {
		return it->second;
	}
}
