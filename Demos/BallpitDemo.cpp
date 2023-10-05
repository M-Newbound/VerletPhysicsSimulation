#include "PhysicsMath.h"
#include "SimulationWorld.h"
#include "Contraint.h"
#include "ForceGeneration.h"
#include "Particle.h"

#include "DemoDisplayer.h"

namespace BallpitDemo {

    // Random number generators for properties
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> sizeDistribution(10.0, 20.0);

    // simlation
    VerletPhysics::SimulationWorld simulation = VerletPhysics::SimulationWorld(1, true);
    VerletPhysics::ConstantAcceleration gravity = VerletPhysics::ConstantAcceleration(VerletPhysics::Vector2(0, 98.1));
    VerletPhysics::BoxedPositionConstraint worldBox = VerletPhysics::BoxedPositionConstraint(VerletPhysics::Vector2(10, 10), VerletPhysics::Vector2(990, 690));

    DemoDisplayer displayer = DemoDisplayer();
    std::vector<const VerletPhysics::Particle*> particles;



    void click(sf::Vector2i mousePosition)
    {
        // Create a new circle body with random properties
        VerletPhysics::Particle* p = simulation.addParticle(VerletPhysics::Vector2(mousePosition.x, mousePosition.y), sizeDistribution(gen));

        gravity.subscribeParticle(p);
        worldBox.subscribeParticle(p);

        particles.push_back(p);
    }

    void update(double deltaTime)
    {
        simulation.update(deltaTime);
        for (const VerletPhysics::Particle* p : particles) displayer.drawParticle(p);
    }

    void runDemo()
    {
        displayer.onClick = click;
        displayer.duringUpdate = update;

        simulation.addConstraint(&worldBox);
        simulation.addGenerator(&gravity);

        displayer.loop();
    }

};
