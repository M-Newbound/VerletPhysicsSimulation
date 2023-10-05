#include "Particle.h"
#include "PhysicsMath.h"

#include <iostream>


using namespace VerletPhysics;

Particle::Particle(Vector2 initialPosition, double radius)
{
	m_positionCurrent = initialPosition;
	m_positionPrevious = initialPosition;
	m_radius = radius;
	m_mass = 3.1415 * radius * radius;

    m_isStatic = false;

	m_forces = Vector2(0, 0);
}

void Particle::integrate(double deltaTime)
{
    if (!m_isStatic) {
        // Calculate the new position using Verlet integration
        const Vector2 acceleration = m_forces / m_mass;
        const Vector2 newPosition = (m_positionCurrent * 2) - m_positionPrevious + acceleration * deltaTime * deltaTime;

        m_positionPrevious = m_positionCurrent;
        m_positionCurrent = newPosition;
    }
    m_forces = Vector2(0, 0);
}

void Particle::addForce(Vector2 force)
{
	m_forces = m_forces + force;
}
