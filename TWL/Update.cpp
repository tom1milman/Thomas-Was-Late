#include <SFML/Graphics.hpp>
#include <sstream>
#include "Engine.h"

using namespace sf;

void Engine::update(float dtAsSeconds)
{
	if (m_NewLevelRequired)
	{
		loadLevel();
	}

	if (m_Playing)
	{
		//Update characters
		m_Thomas.update(dtAsSeconds);
		m_Bob.update(dtAsSeconds);

		//Did both characters reached goal
		if (detectCollision(m_Thomas) && detectCollision(m_Bob))
		{
			m_NewLevelRequired = true;
			m_PassedLevel = true;
			m_SM.playReachGoal();
		}
		else
		{
			detectCollision(m_Bob);
		}

		//Jump on heads
		if (m_Bob.getFeet().intersects(m_Thomas.getHead()))
			m_Bob.stopFalling(m_Thomas.getHead().top);

		else if (m_Thomas.getFeet().intersects(m_Bob.getHead()))
			m_Thomas.stopFalling(m_Bob.getHead().top);

		m_TimeRemaining -= dtAsSeconds;

		if (m_TimeRemaining <= 0)
		{
			m_NewLevelRequired = true;
			m_PassedLevel = false;
		}
	} //End if playing

	//Check if sound fire needs to be played
	vector <Vector2f>::iterator it; 

	for (it = m_FireEmitters.begin(); it != m_FireEmitters.end(); it++)
	{
		//Emitter location
		float posX = it->x;
		float posY = it->y;

		FloatRect localRect(posX - 250, posY - 250, 500, 500);

		if (m_Character1)
		{
			if (m_Thomas.getPosition().intersects(localRect))
			{
				m_SM.playFire(Vector2f(posX, posY), m_Thomas.getCenter());
			}
		}
		else
		{
			if (m_Bob.getPosition().intersects(localRect))
			{
				m_SM.playFire(Vector2f(posX, posY), m_Bob.getCenter());
			}
		}
	}

	//Set views according to screen state
	if (m_SplitScreen)
	{
		m_LeftView.setCenter(m_Thomas.getCenter());
		m_RightView.setCenter(m_Bob.getCenter());
	}
	else
	{
		if (m_Character1)
			m_MainView.setCenter(m_Thomas.getCenter());
		else
			m_MainView.setCenter(m_Bob.getCenter());
	}


	//Update HUD if needed
	m_FrameSinceLastUpdate++;

	if (m_FrameSinceLastUpdate > m_TargetFramesPerHUDUpdate)
	{
		stringstream ssTime;
		stringstream ssLevel;

		//Update time text
		ssTime << (int)m_TimeRemaining;
		m_Hud.setTime(ssTime.str());

		//Update level text
		ssLevel << "Level: " << m_LM.getCurrentLevel();
		m_Hud.setLevel(ssLevel.str());

		m_FrameSinceLastUpdate = 0;
	}

	//Update particle system
	if (m_PS.running())
	{
		m_PS.update(dtAsSeconds);
	}
}