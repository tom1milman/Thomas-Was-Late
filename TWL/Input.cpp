#include "Engine.h"

void Engine::input()
{
	Event event;

	while (m_Window.pollEvent(event))
	{
		if (event.type == Event::KeyPressed)
		{
			//Quit game
			if (Keyboard::isKeyPressed(Keyboard::Escape))
				m_Window.close();

			//Start game
			if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				m_Playing = true;
			}

			//Switch between Thomas and Bob
			if (Keyboard::isKeyPressed(Keyboard::Q))
			{
				m_Character1 = !m_Character1;
			}

			//Switch between full and split screens
			if (Keyboard::isKeyPressed(Keyboard::E))
			{
				m_SplitScreen = !m_SplitScreen;
			}
		}
	}

	//Thomas input
	if (m_Thomas.handleInput())
	{
		m_SM.playJump();
	}

	//Bob input
	if (m_Bob.handleInput())
	{
		m_SM.playJump();
	}
}