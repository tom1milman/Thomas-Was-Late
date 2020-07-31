#include "Engine.h"

void Engine::draw()
{
	m_Window.clear(Color::White);

	//Update shaders
	m_RippleShader.setUniform("uTime", m_GameTimeTotal.asSeconds());

	//Fullscreen
	if (!m_SplitScreen)
	{
		//Switch to background view
		m_Window.setView(m_BGMainView);

		//draw background
		m_Window.draw(m_BackgroundSprite, &m_RippleShader);

		//switch to m_MainView
		m_Window.setView(m_MainView);

		//Draw level
		m_Window.draw(m_VALevel, &m_TextureTiles);

		//Draw characters
		m_Window.draw(m_Thomas.getSprite());
		m_Window.draw(m_Bob.getSprite());

		//Draw particles
		if (m_PS.running())
			m_Window.draw(m_PS);
	}
	//Split screen
	else
	{
#pragma region Thomas Side


		m_Window.setView(m_BGLeftView);

		//Draw background
		m_Window.draw(m_BackgroundSprite, &m_RippleShader);

		//switch to m_LeftView
		m_Window.setView(m_LeftView);

		//Draw level
		m_Window.draw(m_VALevel, &m_TextureTiles);

		//Draw characters - Thomas is on top
		m_Window.draw(m_Bob.getSprite());
		m_Window.draw(m_Thomas.getSprite());

		//Draw particles
		if (m_PS.running())
			m_Window.draw(m_PS);
#pragma endregion

#pragma region Bob Side
		m_Window.setView(m_BGRightView);

		//draw background
		m_Window.draw(m_BackgroundSprite, &m_RippleShader);

		//Switch to m_RightView
		m_Window.setView(m_RightView);

		//Draw level
		m_Window.draw(m_VALevel, &m_TextureTiles);

		//Draw characters - Bob is on top
		m_Window.draw(m_Thomas.getSprite());
		m_Window.draw(m_Bob.getSprite());

		//Draw particles
		if (m_PS.running())
			m_Window.draw(m_PS);
#pragma endregion
	}

	//Draw HUD
	m_Window.setView(m_HudView);

	m_Window.draw(m_Hud.getLevel());
	m_Window.draw(m_Hud.getTime());

	if (!m_Playing)
		m_Window.draw(m_Hud.getMessage());

	//Display everything
	m_Window.display();
}