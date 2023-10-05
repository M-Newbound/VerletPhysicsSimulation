#pragma once
#include "PhysicsMath.h"
#include "Particle.h"
#include "ForceGeneration.h"
#include "Contraint.h"

#include <vector>

namespace VerletPhysics {
    /**
     * Represents a simulation world for Verlet physics.
     *
     * The `SimulationWorld` class manages a collection of particles, force generators, and constraints
     * to simulate the behavior of objects within the Verlet physics framework.
     */
    class SimulationWorld
    {
        std::vector<Particle*> m_particles;        ///< Collection of particles in the simulation.
        std::vector<ForceGenerator*> m_generators; ///< Collection of force generators.
        std::vector<Constraint*> m_constraints;    ///< Collection of constraints.

        const bool c_handleCollisions; ///< Flag indicating whether collision handling is enabled.
        size_t m_steps;                ///< Number of simulation steps.

    public:
        /**
         * Constructs a SimulationWorld object.
         *
         * @param steps Number of simulation steps to perform per update.
         * @param handleCollisions Flag indicating whether collision handling should be enabled.
         */
        SimulationWorld(size_t steps, bool handleCollisions);

        /**
         * Destroys the SimulationWorld object and cleans up allocated resources.
         */
        ~SimulationWorld();

        /**
         * Adds a particle to the simulation world.
         *
         * @param initialPosition The initial position of the particle.
         * @param radius The radius of the particle.
         * @return Pointer to the created Particle object.
         */
        Particle* addParticle(Vector2 initialPosition, double radius);

        /**
         * Adds a force generator to the simulation world.
         *
         * @param generator Pointer to the ForceGenerator object to be added.
         */
        void addGenerator(ForceGenerator* generator);

        /**
         * Adds a constraint to the simulation world.
         *
         * @param constraint Pointer to the Constraint object to be added.
         */
        void addConstraint(Constraint* constraint);

        /**
         * Updates the simulation world for a given time step.
         *
         * @param deltaTime The time step for the simulation update.
         */
        void update(double deltaTime);

    private:
        /**
         * Handles collisions between particles in the simulation world.
         */
        void handleCollisions();

        /**
         * Resolves a collision between two particles.
         *
         * @param particleA Pointer to the first particle involved in the collision.
         * @param particleB Pointer to the second particle involved in the collision.
         */
        void resolveCollision(Particle* particleA, Particle* particleB);

    };

};
