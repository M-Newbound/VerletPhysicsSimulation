#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <iostream>

#include "Particle.h"
#include <SimulationWorld.h>


struct DemoDisplayer
{
    void (*onClick)(sf::Vector2i);
    void (*duringUpdate)(double);
    void loop();

    void drawParticle(const VerletPhysics::Particle* p);
    void drawPairedParticleConstraint(const VerletPhysics::PairedParticleConstraint* c);
};





    
    


