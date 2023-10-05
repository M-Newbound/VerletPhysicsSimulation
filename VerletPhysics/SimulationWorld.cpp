#include "SimulationWorld.h"

using namespace VerletPhysics;

SimulationWorld::SimulationWorld(size_t steps, bool handleCollisions) :
    c_handleCollisions(handleCollisions)
{
    m_steps = steps;
}

VerletPhysics::SimulationWorld::~SimulationWorld()
{
    for (Particle* ptr : m_particles) {
        delete ptr;
    }
    m_particles.clear();
}

Particle* SimulationWorld::addParticle(Vector2 initalPosition, double radius)
{
    Particle* particle = new Particle(initalPosition, radius);
    m_particles.push_back(particle);

    return particle;
}

void VerletPhysics::SimulationWorld::addGenerator(ForceGenerator* generator)
{
    m_generators.push_back(generator);
}

void VerletPhysics::SimulationWorld::addConstraint(Constraint* constraint)
{
    m_constraints.push_back(constraint);
}

void SimulationWorld::update(double deltaTime)
{
    for (size_t i = 0; i < m_steps; i++) {
    
        for (ForceGenerator* generator : m_generators) generator->applyForces();

        for (Particle* particle : m_particles)         particle->integrate(deltaTime / m_steps);

        if (c_handleCollisions) handleCollisions();

        for (Constraint* constraint : m_constraints)   constraint->handleConstraint();

    }

}

void SimulationWorld::handleCollisions()
{
    for (size_t i = 0; i < m_particles.size(); i++)
    {
        for (size_t j = i+1; j < m_particles.size(); j++)
        {
            Particle* particleA = m_particles[i];
            Particle* particleB = m_particles[j];

            // if the two particles are colliding then resolve collision
            double distance = VectorMath::magnitude(particleB->getPosition() - particleA->getPosition());
            if (distance >= particleA->getRadius() + particleB->getRadius()) continue;

            resolveCollision(particleA, particleB);
        
        }
    }
}

void SimulationWorld::resolveCollision(Particle* particleA, Particle* particleB)
{
    Vector2 particleVector = particleB->getPosition() - particleA->getPosition();
    double distance = VectorMath::magnitude(particleVector);
    double overlap = distance - particleA->getRadius() - particleB->getRadius();

    Vector2 collisionNormal = VectorMath::normalize(particleVector);
    double correctionAmount = overlap * 0.5;

    // Move particleA and particleB away from each other along the collision normal
    particleA->updatePosition(particleA->getPosition() + collisionNormal * correctionAmount);
    particleB->updatePosition(particleB->getPosition() - collisionNormal * correctionAmount);

}
