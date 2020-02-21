#include "Collision.h"

void checkCollision(Particle* a, Particle* b) {
	if (static_cast<PhysicsSphere*>(a) != nullptr && static_cast<PhysicsSphere*>(b) != nullptr) {
		sphere_sphere(static_cast<PhysicsSphere*>(a), static_cast<PhysicsSphere*>(b));
	}
}

bool sphere_sphere(PhysicsSphere* a, PhysicsSphere* b) {
	Vector separation = a->getLocation() - b->getLocation();
	Vector normal = ~separation;
	float overlap = a->getRadius() + b->getRadius() - separation.mag();
	return resolve(a, b, overlap, normal, b->getLocation() + normal * overlap);
}

bool resolve(Particle* a, Particle* b, float overlap, Vector normal, Vector contactPoint) {
	if (overlap <= 0) {
		return false;
	}
	float m = 1 / (1 / a->mass + 1 / b->mass);
	Vector penetrator_translation = normal * m * overlap / a->mass;
	a->translate(penetrator_translation);
	contactPoint += penetrator_translation;
	b->translate(-normal * m * overlap / b->mass);
	Vector s1 = contactPoint - a->getLocation();
	Vector s2 = contactPoint - b->getLocation();
	Vector avel = a->velocity + a->avelocity & s1;
	Vector bvel = b->velocity + b->avelocity & s2;

	Vector vel = avel - bvel;

	if (vel * normal >= 0) {
		return false;
	}

	float restitution = 0.5;
	float dv = -(vel * normal * (1 + restitution));
	float newm = 1 / (1 / a->mass + 1 / b->mass + (s1 % normal).mag2() / a->momi.mag() + (s2 % normal).mag2() / b->momi.mag());
	float j = dv * newm;
	a->applyImpulse(normal * j, contactPoint);
	b->applyImpulse(normal * -j, contactPoint);
	return true;
}