#include "Particle.h"

Particle::Particle() {
	force = Vector();
	torque = Vector();
	velocity = Vector();
	avelocity = Vector();
	momi = Vector(1, 1, 1);
	mass = 1;
	graphics = nullptr;
}

void Particle::updatePhysics(const float& dtime) {
	velocity += force / mass * dtime;
	graphics->setLocation(graphics->getLocation() + velocity * dtime);
	avelocity += torque / momi * dtime;
	graphics->setRotation(graphics->getRotation() + avelocity * dtime);
}

void Particle::draw(const Matrix& projection, const Matrix& view) {
	graphics->render(projection, view);
}

void Particle::translate(const Vector& translation) {
	graphics->x += translation.getX();
	graphics->y += translation.getY();
	graphics->z += translation.getZ();
}

void Particle::translate(const float& x, const float& y, const float& z) {
	graphics->x += x;
	graphics->y += y;
	graphics->z += z;
}

void Particle::rotate(const Vector& rotation) {
	graphics->rx += rotation.getX();
	graphics->ry += rotation.getY();
	graphics->rz += rotation.getZ();
}

void Particle::rotate(const float& rx, const float& ry, const float& rz) {
	graphics->rx += rx;
	graphics->ry += ry;
	graphics->rz += rz;
}

void Particle::clearForce() {
	force = Vector();
}

void Particle::applyForce(const Vector& force, const Vector& location) {
	this->force += force;
	avelocity -= (location - graphics->getLocation()) % force;
}

void Particle::applyForce(const float& forcex, const float& forcey, const float& forcez, const Vector& location) {
	applyForce(Vector(forcex, forcey, forcez), location);
}

void Particle::clearTorque() {
	torque = Vector();
}

void Particle::applyTorque(const Vector& torque) {
	this->torque += torque;
}

void Particle::applyTorque(const float& torquex, const float& torquey, const float& torquez) {
	torque += Vector(torquex, torquey, torquez);
}

void Particle::clearVelocity() {
	velocity = Vector();
}

void Particle::addVelocity(const Vector& velocity) {
	this->velocity += velocity;
}

void Particle::addVelocity(const float& velocityx, const float& velocityy, const float& velocityz) {
	velocity += Vector(velocityx, velocityy, velocityz);
}

void Particle::clearAVelocity() {
	avelocity = Vector();
}

void Particle::addAVelocity(const Vector& avelocity) {
	this->avelocity += avelocity;
}

void Particle::addAVelocity(const float& avelocityx, const float& avelocityy, const float& avelocityz) {
	avelocity += Vector(avelocityx, avelocityy, avelocityz);
}

void Particle::applyImpulse(const Vector& impulse, const Vector& location) {
	velocity += impulse / mass;
	avelocity -= (location - graphics->getLocation()) % impulse / momi;
}

void Particle::applyImpulse(const float& impulsex, const float& impulsey, const float& impulsez, const Vector& location) {
	applyImpulse(Vector(impulsex, impulsey, impulsez), location);
}

void Particle::setMomi(const Vector& momi) {
	this->momi = momi;
}

void Particle::setMomi(const float& momix, const float& momiy, const float& momiz) {
	momi = Vector(momix, momiy, momiz);
}

Vector Particle::getLocation() const {
	return graphics->getLocation();
}

void Particle::setLocation(const Vector& pos) {
	graphics->setLocation(pos);
}

void Particle::setLocation(const float& x, const float& y, const float& z) {
	graphics->setLocation(x, y, z);
}

Vector Particle::getScale() const {
	return graphics->getScale();
}

void Particle::setScale(const Vector& scale) {
	graphics->setScale(scale);
}

void Particle::setScale(const float& xscale, const float& yscale, const float& zscale) {
	graphics->setScale(xscale, yscale, zscale);
}

Vector Particle::getRotation() const {
	return graphics->getRotation();
}

void Particle::setRotation(const Vector& rotation) {
	graphics->setRotation(rotation);
}

void Particle::setRotation(const float& xrotation, const float& yrotation, const float& zrotation) {
	graphics->setRotation(xrotation, yrotation, zrotation);
}
