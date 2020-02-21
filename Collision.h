#pragma once
#include "PhysicsSphere.h"

/// <summary> 
/// Checks for collision between two particles, and handles that collisions appropriately.
/// If the combination of particles does not have a resolution function defined, nothing happens.
/// </summary>
/// <param name="a"> The first particle in the potential collision. </param>
/// <param name="b"> The second particle in the potential collision. </param>
void checkCollision(Particle* a, Particle* b);

/// <summary> Determines collision information for two spheres. </summary>
/// <param name="a"> The first particle in the potential collision. </param>
/// <param name="b"> The second particle in the potential collision. </param>
bool sphere_sphere(PhysicsSphere* a, PhysicsSphere* b);

/// <summary> Resolves the collision between two particles given some collision information. </summary>
/// <param name="a"> The first particle in the potential collision. </param>
/// <param name="b"> The second particle in the potential collision. </param>
/// <param name="overlap"> The maximum overlap of the two colliding particles. </param>
/// <param name="normal"> The surface normal at the point of contact. </param>
/// <param name="contactPoint"> The point of contact. </param>
bool resolve(Particle* a, Particle* b, float overlap, Vector normal, Vector contactPoint);
