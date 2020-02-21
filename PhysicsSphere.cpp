#include "PhysicsSphere.h"

PhysicsSphere::PhysicsSphere(const float& x, const float& y, const float& z, const float& r) {
	radius = r;
	graphics = new Sphere(x, y, z, r, r, r);
}

const float& PhysicsSphere::getRadius() const {
	return radius;
}

void PhysicsSphere::setRadius(const float& radius) {
	this->radius = radius;
	graphics->sx = radius;
	graphics->sy = radius;
	graphics->sz = radius;
}