#include "Contraint.h"

using namespace VerletPhysics;

BoxedPositionConstraint::BoxedPositionConstraint(Vector2 cornorA, Vector2 cornorB)
{
	m_maxX = std::max(cornorA.x(), cornorB.x());
	m_maxY = std::max(cornorA.y(), cornorB.y());
	
	m_minX = std::min(cornorA.x(), cornorB.x());
	m_minY = std::min(cornorA.y(), cornorB.y());
}

void BoxedPositionConstraint::processConstraint()
{
	for (Particle* particle : m_particles) {

		Vector2 minPos = particle->getPosition() - Vector2(particle->getRadius(), particle->getRadius());
		Vector2 maxPos = particle->getPosition() + Vector2(particle->getRadius(), particle->getRadius());

		if (minPos.x() < m_minX) {
			particle->updatePosition(Vector2(m_minX + particle->getRadius(), particle->getPosition().y()));
		}
		if (minPos.y() < m_minY) {
			particle->updatePosition(Vector2(particle->getPosition().x(), m_minY + particle->getRadius()));
		}

		if (maxPos.x() > m_maxX) {
			particle->updatePosition(Vector2(m_maxX - particle->getRadius(), particle->getPosition().y()));
		}
		if (maxPos.y() > m_maxY) {
			particle->updatePosition(Vector2(particle->getPosition().x(), m_maxY - particle->getRadius()));
		}

	}
}

void WorldPositionConstraint::subscribeParticle(Particle* subscriber)
{
	m_particles.push_back(subscriber);
}

EncircledPositionConstraint::EncircledPositionConstraint(double radius, Vector2 centerPoint)
{
	m_radius = radius;
	m_centerPoint = centerPoint;
}

void EncircledPositionConstraint::processConstraint()
{
	for (Particle* particle : m_particles) {
		Vector2 displacement = particle->getPosition() - m_centerPoint;
		double distanceToCenter = VectorMath::magnitude(displacement) + particle->getRadius();

		// If the particle is outside the circular boundary, reposition it on the circle's edge
		if (distanceToCenter > m_radius) {

			displacement = VectorMath::normalize(displacement);
			Vector2 newPosition = m_centerPoint + displacement * (m_radius - particle->getRadius());
			particle->updatePosition(newPosition);
		}
	}
}

void PairedParticleConstraint::processConstraint()
{

	Vector2 displacement = c_particleB->getPosition() - c_particleA->getPosition();
	double currentDistance = VectorMath::magnitude(displacement);

	// If the current distance is greater than the maximum allowed distance, adjust their positions
	if (currentDistance > c_maxDistance) {

		displacement = VectorMath::normalize(displacement);
		Vector2 newPositionA = c_particleA->getPosition() + displacement * (currentDistance - c_maxDistance) * 0.5;
		Vector2 newPositionB = c_particleB->getPosition() - displacement * (currentDistance - c_maxDistance) * 0.5;

		c_particleA->updatePosition(newPositionA);
		c_particleB->updatePosition(newPositionB);
	}
}

PairedParticleConstraint::PairedParticleConstraint(Particle* particleA, Particle* particleB, double maxDistance) :
	c_particleA(particleA),
	c_particleB(particleB),
	c_maxDistance(maxDistance)
{}

void VerletPhysics::Constraint::handleConstraint()
{
	if (!m_enabled) return;
	processConstraint();
}
