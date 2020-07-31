#include "Thomas.h"
#include "TextureHolder.h"

Thomas::Thomas()
{
	m_Sprite = Sprite(TextureHolder::GetTexture("graphics/thomas.png"));

	m_JumpDuration = 0.45;
}

bool Thomas::handleInput()
{
	m_JustJumped = false;

	//Jumping
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		if (!m_IsJumping && !m_IsFalling)
		{
			m_IsJumping = true;
			m_TimeThisJump = 0;
			m_JustJumped = true;
		}
	}
	else
	{
		m_IsJumping = false;
		m_IsFalling = true;
	}

	//Move left
	if (Keyboard::isKeyPressed(Keyboard::A))
		m_LeftPressed = true;
	else
		m_LeftPressed = false;

	//Move right
	if (Keyboard::isKeyPressed(Keyboard::D))
		m_RightPressed = true;
	else
		m_RightPressed = false;

	return m_JustJumped;
}