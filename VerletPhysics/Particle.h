#pragma once
#include "PhysicsMath.h"

namespace VerletPhysics {

    /**
     * Represents a particle in the Verlet physics simulation.
     *
     * The `Particle` class is used to simulate a particle in the Verlet physics framework.
     * It stores information about the particle's position, forces acting on it, mass, radius, and
     * whether it is static or movable.
     */
    class Particle {

    private:
        Vector2 m_positionCurrent;    ///< Current position of the particle.
        Vector2 m_positionPrevious;   ///< Previous position of the particle.
        Vector2 m_forces;            ///< Accumulated forces acting on the particle.
        double m_mass;               ///< Mass of the particle.
        double m_radius;             ///< Radius of the particle.
        bool m_isStatic;             ///< Flag indicating whether the particle is static.

    public:
        /**
         * Constructs a Particle object.
         *
         * @param initialPosition The initial position of the particle.
         * @param radius The radius of the particle.
         */
        Particle(Vector2 initialPosition, double radius);

        /**
         * Integrates the particle's position over time.
         *
         * @param deltaTime The time step for the integration.
         */
        void integrate(double deltaTime);

        /**
         * Adds a force to the particle.
         *
         * @param force The force to be added to the particle.
         */
        void addForce(Vector2 force);

        /**
         * Updates the current position of the particle.
         *
         * @param newPosition The new position to set for the particle.
         * @note If the particle is static, this operation is ignored.
         */
        void updatePosition(Vector2 newPosition) { if (m_isStatic) return; m_positionCurrent = newPosition; }

        /**
         * Resets the particle's position to a new position.
         *
         * @param newPosition The new position to set for both current and previous positions.
         */
        void resetPosition(Vector2 newPosition) { m_positionCurrent = newPosition; m_positionPrevious = newPosition; }

        /**
         * Sets the static state of the particle.
         *
         * @param newState `true` if the particle should be static, `false` if it should be movable.
         */
        void setStaticState(bool newState) { m_isStatic = newState; }

        /**
         * Gets the radius of the particle.
         *
         * @return The radius of the particle.
         */
        double getRadius() const { return m_radius; }

        /**
         * Gets the mass of the particle.
         *
         * @return The mass of the particle.
         */
        double getMass() const { return m_mass; }

        /**
         * Gets the current position of the particle.
         *
         * @return The current position of the particle.
         */
        Vector2 getPosition() const { return m_positionCurrent; }

        /**
         * Gets the previous position of the particle.
         *
         * @return The previous position of the particle.
         */
        Vector2 getPreviousPosition() const { return m_positionPrevious; }
    };
}
