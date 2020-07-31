#include "Engine.h"

bool Engine::detectCollision(PlayableCharacter& character)
{
	bool reachedGoal = false;

	FloatRect detectionZone = character.getPosition();

	//Float rect to test each block
	FloatRect block;

	block.width = TILE_SIZE;
	block.height = TILE_SIZE;

	//collision zone around Thomas
	int startX = (int)(detectionZone.left / TILE_SIZE) - 1;
	int startY = (int)(detectionZone.top / TILE_SIZE) - 1;

	int endX = (int)(detectionZone.left / TILE_SIZE) + 2;
	int endY = (int)(detectionZone.top / TILE_SIZE) + 3;

	if (startX < 0)
		startX = 0;

	if (startY < 0)
		startY = 0;

	if (endX >= m_LM.getLevelSize().x)
		endX = m_LM.getLevelSize().x;

	if (endY >= m_LM.getLevelSize().y)
		endY = m_LM.getLevelSize().y;

	//check if character fell out of the map
	FloatRect level(0, 0, m_LM.getLevelSize().x * TILE_SIZE, m_LM.getLevelSize().y * TILE_SIZE);

	if (!character.getPosition().intersects(level))
		character.spawn(m_LM.getStartPosition(), GRAVITY);

	for (int x = startX; x < endX; x++)
	{
		for (int y = startY; y < endY; y++)
		{
			//init start position
			block.left = x * TILE_SIZE;
			block.top = y * TILE_SIZE;

			//check for fire or water
			if (m_arrayLevel[y][x] == 2 || m_arrayLevel[y][x] == 3)
			{
				if (character.getHead().intersects(block))
				{
					character.spawn(m_LM.getStartPosition(), GRAVITY);

					if (m_arrayLevel[y][x] == 2) // fire
					{
						m_SM.playFallInFire();
					}

					else //water
					{
						m_SM.playFallInWater();
					}
				}
			}

			//check if regular tile
			if (m_arrayLevel[y][x] == 1)
			{
				if (character.getRight().intersects(block))
					character.stopRight(block.left);

				else if (character.getLeft().intersects(block))
					character.stopLeft(block.left);

				if (character.getFeet().intersects(block))
					character.stopFalling(block.top);

				else if (character.getHead().intersects(block))
					character.stopJump();
			}

			if (!m_PS.running())
			{
				if (m_arrayLevel[y][x] == 2 || m_arrayLevel[y][x] == 3)
				{
					if (character.getFeet().intersects(block))
						m_PS.emitParticles(character.getCenter());
				}
			}

			//Did character reach goal
			if (m_arrayLevel[y][x] == 4)
				reachedGoal = true;
		}
	}

	return reachedGoal;
}