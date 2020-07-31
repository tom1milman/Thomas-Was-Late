#include "Engine.h"

using namespace sf;
using namespace std;

//Goes over fire blocks, and adds them as emitters to the vector
//skips any fire block in radious of 6 tiles from each emitter
void Engine::populateEmitters(vector <Vector2f>& vSoundEmitters, int** arrayLevel)
{
	//Empty vector
	vSoundEmitters.empty();

	//Keep track of previous emitter
	FloatRect previousEmitter;


	for (int x = 0; x < (int)m_LM.getLevelSize().x; x++)
	{
		for (int y = 0; y < (int)m_LM.getLevelSize().y; y++)
		{
			//if Fire block
			if (arrayLevel[y][x] == 2)
			{
				int xTileSize = x * TILE_SIZE;
				int yTileSize = y * TILE_SIZE;

				//If not too close to previous emitter
				if (!FloatRect(xTileSize, yTileSize, TILE_SIZE, TILE_SIZE).intersects(previousEmitter))
				{
					vSoundEmitters.push_back(Vector2f(xTileSize, yTileSize));

					previousEmitter.left = xTileSize;
					previousEmitter.top = yTileSize;
					previousEmitter.width = TILE_SIZE * 6;
					previousEmitter.height = TILE_SIZE * 6;
				}
			}
		}
	}
}