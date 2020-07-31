#include <SFML/Graphics.hpp>
#include "ParticleSystem.h"

using namespace sf;
using namespace std;

void ParticleSystem::init(int numParticles)
{
	m_Vertices.setPrimitiveType(Points);
	m_Vertices.resize(numParticles);

	//Create particles
	for (int i = 0; i < numParticles; i++)
	{
		srand(time(0) + i);
		float angle = (rand() % 360) * 3.14f / 180.0f;
		float speed = (rand() % 360) + 500.0f;

		Vector2f direction;

		direction = Vector2f(cos(angle) * speed, sin(angle) * speed);

		m_Particles.push_back(Particle(direction));
	}
}

void ParticleSystem::update(float dt)
{
	m_Duration -= dt;
	vector<Particle>::iterator i;
	int currentVertex = 0;

	for (i = m_Particles.begin(); i != m_Particles.end(); i++)
	{
		//Update particles
		i->update(dt);

		m_Vertices[currentVertex].position = i->getPosition();

		currentVertex++;
	}

	if (m_Duration < 0)
		m_IsRunning = false;
}

void ParticleSystem::emitParticles(Vector2f startPosition)
{
	m_IsRunning = true;
	m_Duration = 2;

	vector<Particle>::iterator i;
	int currentVertex = 0;

	for (i = m_Particles.begin(); i != m_Particles.end(); i++)
	{
		m_Vertices[currentVertex].color = Color::Yellow;
		i->setPosition(startPosition);

		currentVertex++;
	}
}

void ParticleSystem::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_Vertices, states);
}

bool ParticleSystem::running()
{
	return m_IsRunning;
}