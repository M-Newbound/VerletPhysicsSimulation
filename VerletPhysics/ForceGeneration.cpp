#include "ForceGeneration.h"

VerletPhysics::ConstantAcceleration::ConstantAcceleration(Vector2 acceleration) :
	m_accelerationFactor(acceleration)
{}

void VerletPhysics::ConstantAcceleration::subscribeParticle(Particle* subscriber)
{
	m_particles.push_back(subscriber);
}

void VerletPhysics::ConstantAcceleration::applyForces()
{
	for (Particle* particle : m_particles)
	{
		particle->addForce(m_accelerationFactor * particle->getMass());
	}
}
