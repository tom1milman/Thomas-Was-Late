#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class PlayableCharacter
{
protected:
	Sprite m_Sprite;

	//Jump duration
	float m_JumpDuration;

	//Character state
	bool m_IsJumping;
	bool m_IsFalling;

	//character movement direction
	bool m_LeftPressed;
	bool m_RightPressed;
		
	//Duration of jump
	float m_TimeThisJump;

	//Did player just jumped
	bool m_JustJumped = false;

private:
	float m_Gravity;

	//Character speed
	float m_Speed = 400;

	//Character position
	Vector2f m_Position;

	//Character body parts 
	FloatRect m_Feet;
	FloatRect m_Head;
	FloatRect m_Right;
	FloatRect m_Left;

	//Texutre
	Texture m_Texture;

public:
	void spawn(Vector2f startPosition, float gravity);

	bool virtual handleInput() = 0;

	//Character's position
	FloatRect getPosition();

	//Return character's parts positions
	FloatRect getFeet();
	FloatRect getHead();
	FloatRect getRight();
	FloatRect getLeft();

	//Get sprite
	Sprite getSprite();

	//Stops character
	void stopFalling(float position);
	void stopRight(float position);
	void stopLeft(float position);
	void stopJump();

	//Character center
	Vector2f getCenter();

	//Update each frame
	void update(float elapsedTime);
};