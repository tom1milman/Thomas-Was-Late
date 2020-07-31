#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TextureHolder.h"
#include "LevelManager.h"
#include <sstream>
#include <fstream>

using namespace sf;
using namespace std;

int** LevelManager::nextLevel(VertexArray& rVaLevel)
{
	m_LevelSize.x = 0;
	m_LevelSize.y = 0;

	m_CurrentLevel++;

	if (m_CurrentLevel > NUM_LEVELS)
	{
		m_CurrentLevel = 1;
		m_TimeModifier = 0.1f;
	}

	string levelToLoad;

	switch (m_CurrentLevel)
	{
	case 1:
		levelToLoad = "levels/level1.txt";
		m_StartPosition.x = 100;
		m_StartPosition.y = 100;
		m_BaseTimeLimit = 60.0f;
		break;
	case 2:
		levelToLoad = "levels/level2.txt";
		m_StartPosition.x = 100;
		m_StartPosition.y = 3600;
		m_BaseTimeLimit = 100.0f;
		break;
	case 3:
		levelToLoad = "levels/level3.txt";
		m_StartPosition.x = 1250;
		m_StartPosition.y = 0;
		m_BaseTimeLimit = 30.0f;
		break;
	case 4:
		levelToLoad = "levels/level4.txt";
		m_StartPosition.x = 50;
		m_StartPosition.y = 200;
		m_BaseTimeLimit = 50.0f;
		break;
	} //End switch case

	//get Level file
	ifstream inputFile(levelToLoad);
	string s;

	//Record level size
	while (getline(inputFile, s))
	{
		++m_LevelSize.y;
	}

	m_LevelSize.x = s.length();

	//Go to start of file
	inputFile.clear();
	inputFile.seekg(0, ios::beg);

	//Prepare 2d array for level values
	int** arrayLevel = new int*[m_LevelSize.y];
	for (int i = 0; i < m_LevelSize.y; i++)
	{
		arrayLevel[i] = new int[m_LevelSize.x];
	}

	//Loop through file and store values in 2d array
	string row;
	int y = 0;
	while (inputFile >> row)
	{
		for (int x = 0; x < row.length(); x++)
		{
			const char val = row[x];
			arrayLevel[y][x] = atoi(&val);
		}

		y++;
	}

	//Close file
	inputFile.close();

	//Init rVaLevel
	rVaLevel.setPrimitiveType(Quads);
	rVaLevel.resize(m_LevelSize.x * m_LevelSize.y * VERTS_IN_QUAD);

	int currentVertex = 0;

	for (int x = 0; x < m_LevelSize.x; x++)
	{
		for (int y = 0; y < m_LevelSize.y; y++)
		{
			//Position vertex in currect quad
			int xTileSize = x * TILE_SIZE;
			int yTileSize = y * TILE_SIZE;

			rVaLevel[currentVertex + 0].position = Vector2f(xTileSize, yTileSize);

			rVaLevel[currentVertex + 1].position = Vector2f(xTileSize + TILE_SIZE, yTileSize);

			rVaLevel[currentVertex + 2].position = Vector2f(xTileSize + TILE_SIZE, yTileSize + TILE_SIZE);

			rVaLevel[currentVertex + 3].position = Vector2f(xTileSize, yTileSize + TILE_SIZE);

			//Choose tile from sprite sheet
			int verticalOffset = arrayLevel[y][x] * TILE_SIZE;

			rVaLevel[currentVertex + 0].texCoords = Vector2f(0, 0 + verticalOffset);

			rVaLevel[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);

			rVaLevel[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);

			rVaLevel[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);

			currentVertex = currentVertex + VERTS_IN_QUAD;
		}
	}

	return arrayLevel;
}

Vector2i LevelManager::getLevelSize()
{
	return m_LevelSize;
}

int LevelManager::getCurrentLevel()
{
	return m_CurrentLevel;
}

float LevelManager::getTimeLimit()
{
	return m_BaseTimeLimit * m_TimeModifier;
}

Vector2f LevelManager::getStartPosition()
{
	return m_StartPosition;
}