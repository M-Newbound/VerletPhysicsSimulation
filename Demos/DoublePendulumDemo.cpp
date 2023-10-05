#include "PhysicsMath.h"
#include "SimulationWorld.h"
#include "Contraint.h"
#include "ForceGeneration.h"
#include "Particle.h"

#include "DemoDisplayer.h"

namespace DoublePendulumDemo {

    
    // simlation
    VerletPhysics::SimulationWorld simulation = VerletPhysics::SimulationWorld(10, false);
    VerletPhysics::ConstantAcceleration gravity = VerletPhysics::ConstantAcceleration(VerletPhysics::Vector2(0, 98.1));

    DemoDisplayer displayer = DemoDisplayer();
    std::vector<const VerletPhysics::Particle*> particles;
    std::vector<const VerletPhysics::PairedParticleConstraint*> ppConstraints;

    void click(sf::Vector2i mousePosition)
    {
    }

    void update(double deltaTime)
    {
        simulation.update(deltaTime);

        for (const VerletPhysics::PairedParticleConstraint* c : ppConstraints) displayer.drawPairedParticleConstraint(c);
        for (const VerletPhysics::Particle* p : particles) displayer.drawParticle(p);
    }

    void runDemo()
    {
        displayer.onClick = click;
        displayer.duringUpdate = update;

        displayer.onClick = click;
        displayer.duringUpdate = update;

        simulation.addGenerator(&gravity);

        VerletPhysics::Particle* anchor = simulation.addParticle(VerletPhysics::Vector2(500, 250), 10);
        VerletPhysics::Particle* p1 = simulation.addParticle(VerletPhysics::Vector2(620, 280), 10);
        VerletPhysics::Particle* p2 = simulation.addParticle(VerletPhysics::Vector2(700, 376), 10);

        anchor->setStaticState(true);
        gravity.subscribeParticle(p1);
        gravity.subscribeParticle(p2);

        VerletPhysics::PairedParticleConstraint constraintA(anchor, p1, 150);
        VerletPhysics::PairedParticleConstraint constraintB(p1, p2, 150);

        ppConstraints.push_back(&constraintA);
        ppConstraints.push_back(&constraintB);

        simulation.addConstraint(&constraintA);
        simulation.addConstraint(&constraintB);

        particles.push_back(anchor);
        particles.push_back(p1);
        particles.push_back(p2);

        displayer.loop();
    }
};

