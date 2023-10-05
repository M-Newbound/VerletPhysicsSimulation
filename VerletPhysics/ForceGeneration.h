#pragma once

#include <vector>
#include "Particle.h"

namespace VerletPhysics {

    /**
     * Base class for force generators in the Verlet physics simulation.
     *
     * The `ForceGenerator` struct defines a base class for force generators that can apply
     * forces to particles within the Verlet physics framework. Derived classes should implement
     * the `applyForces` method to provide specific force generation behavior.
     */
    struct ForceGenerator
    {
        /**
         * Applies forces to particles.
         *
         * Derived classes should implement this method to apply specific forces to particles.
         */
        virtual void applyForces() = 0;
    };

    /**
     * Represents a constant acceleration force generator.
     *
     * The `ConstantAcceleration` class is a specific force generator that applies a constant
     * acceleration to a collection of particles. It is used to simulate gravity, wind, or any
     * other constant force affecting particles.
     */
    class ConstantAcceleration : public ForceGenerator
    {
        std::vector<Particle*> m_particles; ///< Collection of particles affected by the constant acceleration.
        const Vector2 m_accelerationFactor; ///< The constant acceleration to be applied.

    public:
        /**
         * Constructs a ConstantAcceleration object.
         *
         * @param acceleration The constant acceleration vector to be applied.
         */
        ConstantAcceleration(Vector2 acceleration);

        /**
         * Subscribes a particle to be affected by the constant acceleration.
         *
         * @param subscriber Pointer to the Particle object to be affected.
         */
        void subscribeParticle(Particle* subscriber);

        /**
         * Applies the constant acceleration to the subscribed particles.
         *
         * Overrides the base class's `applyForces` method to apply the constant acceleration
         * to the particles in the subscription list.
         */
        virtual void applyForces() override;
    };
};
