#pragma once
#include "Particle.h"
#include <vector>

namespace VerletPhysics {

    /**
     * Base class for constraints in the Verlet physics simulation.
     *
     * The `Constraint` class defines a base class for constraints that can be applied
     * to particles within the Verlet physics framework. Derived classes should implement
     * the `processConstraint` method to provide specific constraint behavior.
     */
    class Constraint
    {
    protected:
        bool m_enabled = true; ///< Flag indicating whether the constraint is enabled.
        virtual void processConstraint() = 0; ///< Virtual method to process the constraint.

    public:

        /**
         * Handles the constraint.
         *
         * Processes the constraint only if enabled.
         */
        void handleConstraint();

        /**
         * Enables the constraint.
         */
        void enable() { m_enabled = true; }

        /**
         * Disables the constraint.
         */
        void disable() { m_enabled = false; }

        /**
         * Checks if the constraint is enabled.
         *
         * @return `true` if the constraint is enabled, `false` otherwise.
         */
        bool isEnabled() { return m_enabled; }
    };


    /**
     * Base class for position-based constraints in the Verlet physics simulation.
     *
     * The `WorldPositionConstraint` class is a base class for constraints that operate based on
     * the positions of particles. Derived classes should implement the `processConstraint` method
     * to provide specific position-based constraint behavior.
     */
    class WorldPositionConstraint : public Constraint
    {
    protected:
        std::vector<Particle*> m_particles; ///< Collection of particles affected by the constraint.

    public:

        /**
         * Subscribes a particle to be affected by the constraint.
         *
         * @param subscriber Pointer to the Particle object to be affected.
         */
        void subscribeParticle(Particle* subscriber);

        /**
         * Processes the position-based constraint.
         */
        virtual void processConstraint() = 0;
    };


    /**
     * Represents a boxed position constraint in the Verlet physics simulation.
     *
     * The `BoxedPositionConstraint` class is a specific position-based constraint that confines
     * particles within a rectangular area defined by two corner points.
     */
    class BoxedPositionConstraint : public WorldPositionConstraint
    {
        double m_minX; ///< Minimum X-coordinate of the box.
        double m_minY; ///< Minimum Y-coordinate of the box.
        double m_maxX; ///< Maximum X-coordinate of the box.
        double m_maxY; ///< Maximum Y-coordinate of the box.

    public:

        /**
         * Constructs a BoxedPositionConstraint object.
         *
         * @param cornerA The first corner point of the rectangular area.
         * @param cornerB The second corner point of the rectangular area.
         */
        BoxedPositionConstraint(Vector2 cornerA, Vector2 cornerB);

        /**
         * Processes the boxed position constraint, confining particles within the defined box.
         */
        virtual void processConstraint() override;
    };


    /**
     * Represents an encircled position constraint in the Verlet physics simulation.
     *
     * The `EncircledPositionConstraint` class is a specific position-based constraint that confines
     * particles within a circular area defined by a center point and a radius.
     */
    class EncircledPositionConstraint : public WorldPositionConstraint
    {
        double m_radius;       ///< Radius of the circular area.
        Vector2 m_centerPoint; ///< Center point of the circular area.

    public:

        /**
         * Constructs an EncircledPositionConstraint object.
         *
         * @param radius The radius of the circular area.
         * @param centerPoint The center point of the circular area.
         */
        EncircledPositionConstraint(double radius, Vector2 centerPoint);

        /**
         * Processes the encircled position constraint, confining particles within the defined circle.
         */
        virtual void processConstraint() override;
    };


    /**
     * Represents a paired particle constraint in the Verlet physics simulation.
     *
     * The `PairedParticleConstraint` class is a specific constraint that enforces a maximum distance
     * between two particles.
     */
    class PairedParticleConstraint : public Constraint
    {
        Particle* const c_particleA; ///< Pointer to the first particle involved in the constraint.
        Particle* const c_particleB; ///< Pointer to the second particle involved in the constraint.
        const double c_maxDistance; ///< Maximum allowed distance between the particles.

    public:

        /**
         * Constructs a PairedParticleConstraint object.
         *
         * @param particleA Pointer to the first particle involved in the constraint.
         * @param particleB Pointer to the second particle involved in the constraint.
         * @param maxDistance The maximum allowed distance between the particles.
         */
        PairedParticleConstraint(Particle* particleA, Particle* particleB, double maxDistance);

        /**
         * Processes the paired particle constraint, enforcing the maximum distance between the particles.
         */
        virtual void processConstraint() override;

        /**
         * Gets a pointer to the first particle involved in the constraint.
         *
         * @return Pointer to the first particle.
         */
        Particle* getParticleA() const { return c_particleA; }

        /**
         * Gets a pointer to the second particle involved in the constraint.
         *
         * @return Pointer to the second particle.
         */
        Particle* getParticleB() const { return c_particleB; }
    };
}
