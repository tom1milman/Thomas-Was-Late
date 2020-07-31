#include "Particle.h"

Particle::Particle(Vector2f direction)
{
	m_Velocity.x = direction.x;
	m_Velocity.y = direction.y;
}

void Particle::update(float dtAsSeconds)
{
	//Move particle
	m_position += m_Velocity * dtAsSeconds;
}

void Particle::setPosition(Vector2f position)
{
	m_position = position;
}

Vector2f Particle::getPosition()
{
	return m_position;
}