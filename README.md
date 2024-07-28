# Verlet Particle Simulator in C++

This project is a Verlet Particle Simulator implemented from scratch in C++ with a ballpit demo and a cloth simulation.

## Project Description

The Verlet Particle Simulator uses Verlet integration to simulate the motion of particles under various forces. The project includes two main demos:

- **Ballpit Demo**: Simulates a collection of particles (balls) interacting within a confined space.
- **Cloth Simulation**: Simulates a cloth using a grid of interconnected particles with spring constraints to model the cloth's behavior.

## Why I Undertook This Project
### Interest in Physics Simulations

I have a strong interest in physics simulations and their applications in computer graphics and games. Developing a Verlet particle simulator from scratch provided an opportunity to explore these concepts in depth.
### Challenge of Realistic Simulations

Creating realistic simulations involves solving complex problems such as accurate collision detection and response, numerical stability, and efficient computation. Tackling these challenges has been a valuable learning experience.
## What I Learned
### Fundamentals of Verlet Integration

I learned about Verlet integration, a numerical method used to integrate Newton's equations of motion. This method is particularly well-suited for simulating particle systems due to its stability and simplicity.
### Collision Detection and Response

Implementing collision detection and response for both the ballpit and cloth simulations taught me about various techniques for detecting and resolving collisions between particles and with boundaries. This includes handling edge cases and ensuring realistic interactions.

### Spring Constraints and Cloth Simulation

The cloth simulation required implementing spring constraints to model the behavior of a flexible surface.

## What I Would Do Differently

- **Enhance Collision Detection**: Implement more sophisticated collision detection techniques, such as bounding volume hierarchies (BVH) or spatial partitioning, to improve the accuracy and efficiency of collision handling.
- **Add Friction and Air Resistance**: Introduce friction and air resistance to the simulations for more realistic particle interactions and motion.
- **Expand Simulation Types**: Explore additional types of simulations, such as fluid dynamics or rigid body simulations, to broaden the scope of the project.
