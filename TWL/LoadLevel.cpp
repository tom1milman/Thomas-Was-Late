#include "Engine.h"

void Engine::loadLevel()
{
	m_Playing = false;

	if (m_PassedLevel)
	{
		//Delete previos allocated memory
		for (int i = 0; i < m_LM.getLevelSize().y; i++)
			delete[] m_arrayLevel[i];

		delete[] m_arrayLevel;

		//Load new level
		m_arrayLevel = m_LM.nextLevel(m_VALevel);

		//Set fire emitters
		populateEmitters(m_FireEmitters, m_arrayLevel);
	}

	//Update time for level
	m_TimeRemaining = m_LM.getTimeLimit();

	//Spawn characters
	m_Thomas.spawn(m_LM.getStartPosition(), GRAVITY);
	m_Bob.spawn(m_LM.getStartPosition(), GRAVITY);

	m_NewLevelRequired = false;
	m_PassedLevel = false;
}