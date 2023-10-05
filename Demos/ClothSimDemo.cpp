#include "PhysicsMath.h"
#include "SimulationWorld.h"
#include "Contraint.h"
#include "ForceGeneration.h"
#include "Particle.h"

#include "DemoDisplayer.h"
#include "ClothSimDemo.h"

namespace ClothSimDemo
{

    
    // simlation
    VerletPhysics::SimulationWorld simulation = VerletPhysics::SimulationWorld(3, true);
    VerletPhysics::ConstantAcceleration gravity = VerletPhysics::ConstantAcceleration(VerletPhysics::Vector2(0, 150));

    DemoDisplayer displayer = DemoDisplayer();
    const int ROWS = 10;
    const int COLUMNS = 20;

    VerletPhysics::Particle* particles[ROWS][COLUMNS];

    std::vector<const VerletPhysics::PairedParticleConstraint*> ppConstraints;

    bool isPointIntersectingLineSegment(double x, double y, double x1, double y1, double x2, double y2, double leeway) {
        // Check if the point is within the bounding box of the extended line segment
        double minX = std::min(x1, x2) - leeway;
        double minY = std::min(y1, y2) - leeway;
        double maxX = std::max(x1, x2) + leeway;
        double maxY = std::max(y1, y2) + leeway;

        if (x < minX || x > maxX || y < minY || y > maxY) {
            return false; // The point is outside the bounding box
        }

        // Calculate the distance from the point to the line defined by the line segment
        double distance = std::abs((x2 - x1) * (y1 - y) - (x1 - x) * (y2 - y1)) /
            std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

        return distance <= leeway;
    }

    void click(sf::Vector2i mousePosition)
    {
        for (size_t i = 0; i < ppConstraints.size(); i++)
        {
            if (!((VerletPhysics::Constraint*)ppConstraints[i])->isEnabled()) continue;
            
            double x = mousePosition.x;
            double y = mousePosition.y;

            double x1 = ppConstraints[i]->getParticleA()->getPosition().x();
            double y1 = ppConstraints[i]->getParticleA()->getPosition().y();

            double x2 = ppConstraints[i]->getParticleB()->getPosition().x();
            double y2 = ppConstraints[i]->getParticleB()->getPosition().y();

            double leeway = 5;
            
            if (!isPointIntersectingLineSegment(x, y, x1, y1, x2, y2, leeway)) continue;

            ((VerletPhysics::Constraint*)ppConstraints[i])->disable();
            return;
        }
    }

    void update(double deltaTime)
    {
        simulation.update(deltaTime);

        for (const VerletPhysics::PairedParticleConstraint* c : ppConstraints) displayer.drawPairedParticleConstraint(c);
        for (size_t i = 0; i < ROWS; i++) for (size_t j = 0; j < COLUMNS; j++) displayer.drawParticle(particles[i][j]);
    }

    void generateCloth()
    {
        const double STARTING_X = 50;
        const double STARTING_Y = 50;

        const double OFFSET_X = 30;
        const double OFFSET_Y = 30;

        // setup particles
        for (size_t i = 0; i < ROWS; i++) {
            for (size_t j = 0; j < COLUMNS; j++) {
                VerletPhysics::Vector2 position = VerletPhysics::Vector2(STARTING_X + j*OFFSET_X, STARTING_Y + i*OFFSET_Y);
                VerletPhysics::Particle* p = simulation.addParticle(position, 5);

                if (i == 0) p->setStaticState(true);
                else gravity.subscribeParticle(p);

                particles[i][j] = p;
            }
        }

        // setup constraints
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLUMNS; j++) {
                double maxDistance = std::sqrt(OFFSET_X * OFFSET_X + OFFSET_Y * OFFSET_Y) - 1;
                std::vector<VerletPhysics::Particle*> neighbors;

                if (i - 1 >= 0) neighbors.push_back(particles[i-1][j]);
                if (i + 1 < ROWS) neighbors.push_back(particles[i+1][j]);
                if (j - 1 >= 0) neighbors.push_back(particles[i][j]);
                if (j + 1 < COLUMNS) neighbors.push_back(particles[i][j+1]);

                for (VerletPhysics::Particle* p : neighbors)
                {
                    VerletPhysics::PairedParticleConstraint* ppConstraint = new VerletPhysics::PairedParticleConstraint(particles[i][j], p, maxDistance);
                    simulation.addConstraint(ppConstraint);
                    ppConstraints.push_back(ppConstraint);
                }
            }
        }
    }

    void runDemo()
    {
        displayer.onClick = click;
        displayer.duringUpdate = update;

        displayer.onClick = click;
        displayer.duringUpdate = update;

        simulation.addGenerator(&gravity);

        generateCloth();
        int t = 4;
        displayer.loop();
    }
};
