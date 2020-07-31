#include "Bob.h"
#include "TextureHolder.h"

Bob::Bob()
{
	m_Sprite = Sprite(TextureHolder::GetTexture("graphics/bob.png"));

	m_JumpDuration = 0.25;
}

bool Bob::handleInput()
{
	m_JustJumped = false;

	//Jumping
	if (Keyboard::isKeyPressed(Keyboard::Up))
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
	if (Keyboard::isKeyPressed(Keyboard::Left))
		m_LeftPressed = true;
	else
		m_LeftPressed = false;

	//Move right
	if (Keyboard::isKeyPressed(Keyboard::Right))
		m_RightPressed = true;
	else
		m_RightPressed = false;

	return m_JustJumped;
}