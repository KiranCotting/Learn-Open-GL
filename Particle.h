#pragma once
#include "Vector.h"
#include "GraphicsShape.h"

/// <summary> The basic physics object, contains physical properties and movement information. </summary>
class Particle
{
public:
	/// <summary> The the force applied to this object during this frame. Can be modified directly. </summary>
	Vector force;
	/// <summary> The torque applied to this object during this frame. Can be modified directly. </summary>
	Vector torque;
	/// <summary> The speed at which this object is moving. Can be modified directly. </summary>
	Vector velocity;
	/// <summary> The speed at which this object is rotating. Can be modified directly. </summary>
	Vector avelocity;
	/// <summary> The moment of inertia of this object. Can be modified directly. </summary>
	Vector momi;
	/// <summary> The mass of this object. Can be modified directly. </summary>
	float mass;
	/// <summary> Called once per frame on this object to update its physics. </summary>
	/// <param name="dtime"> The amount of time since the last frame, in seconds. </param>
	void updatePhysics(const float& dtime);
	/// <summary> Called once per frame on this object to update its graphics. </summary>
	/// <param name="projection"> The projection matrix. </param>
	/// <param name="view"> The view matrix. </param>
	void draw(const Matrix& projection, const Matrix& view);
	/// <summary> Translate this shape. </summary>
	/// <param name="translation"> The amount to translate by. </param>
	void translate(const Vector& translation);
	/// <summary> Translate this shape. </summary>
	/// <param name="x"> The amount to translate by along the x-axis. </param>
	/// <param name="y"> The amount to translate by along the y-axis. </param>
	/// <param name="z"> The amount to translate by along the z-axis. </param>
	void translate(const float& x, const float& y, const float& z);
	/// <summary> Rotate this shape. </summary>
	/// <param name="rotation"> The amount to rotate by. </param>
	void rotate(const Vector& rotation);
	/// <summary> Rotate this shape. </summary>
	/// <param name="rx"> The amount to rotate around the x-axis. </param>
	/// <param name="ry"> The amount to rotate around the y-axis. </param>
	/// <param name="rz"> The amount to rotate around the z-axis. </param>
	void rotate(const float& rx, const float& ry, const float& rz);
	/// <summary> Resets the force on this object to zero, stopping all acceleration. </summary>
	void clearForce();
	/// <summary> Apply a new force to this object. </summary>
	/// <param name="force"> The force to be applied. </param>
	void applyForce(const Vector& force, const Vector& location);
	/// <summary> Apply a new force to this object. </summary>
	/// <param name="forcex"> The force to be applied along the x-axis. </param>
	/// <param name="forcey"> The force to be applied along the y-axis. </param>
	/// <param name="forcez"> The force to be applied along the z-axis. </param>
	void applyForce(const float& forcex, const float& forcey, const float& forcez, const Vector& location);
	/// <summary> Resets the torque on this object to zero, stopping all angular acceleration. </summary>
	void clearTorque();
	/// <summary> Apply a new torque to this object. </summary>
	/// <param name="torque"> The torque to be applied. </param>
	void applyTorque(const Vector& torque);
	/// <summary> Apply a new torque to this object. </summary>
	/// <param name="torquex"> The torque to be applied about the x-axis. </param>
	/// <param name="torquey"> The torque to be applied about the y-axis. </param>
	/// <param name="torquez"> The torque to be applied about the z-axis. </param>
	void applyTorque(const float& torquex, const float& torquey, const float& torquez);
	/// <summary> Resets the velocity of this object to zero, stopping all prior translation. </summary>
	void clearVelocity();
	/// <summary> Add to this object's velocity. </summary>
	/// <param name="velocity"> The velocity to be added. </param>
	void addVelocity(const Vector& velocity);
	/// <summary> Add to this object's velocity. </summary>
	/// <param name="velocityx"> The velocity to be added along the x-axis. </param>
	/// <param name="velocityy"> The velocity to be added along the y-axis. </param>
	/// <param name="velocityz"> The velocity to be added along the z-axis. </param>
	void addVelocity(const float& velocityx, const float& velocityy, const float& velocityz);
	/// <summary> Resets the angular velocity of this object to zero, stopping all prior rotation. </summary>
	void clearAVelocity();
	/// <summary> Add to this object's angular velocity. </summary>
	/// <param name="avelocity"> The angular velocity to be added. </param>
	void addAVelocity(const Vector& avelocity);
	/// <summary> Add to this object's angular velocity. </summary>
	/// <param name="avelocityx"> The angular velocity to be added about the x-axis. </param>
	/// <param name="avelocityy"> The angular velocity to be added about the y-axis. </param>
	/// <param name="avelocityz"> The angular velocity to be added about the z-axis. </param>
	void addAVelocity(const float& avelocityx, const float& avelocityy, const float& avelocityz);
	/// <summary> Apply an impulse to this object, changing its velocity by the same amount regardless of time since last frame. </summary>
	/// <param name="impulse"> The impulse to be applied. </param>
	/// <param name="location"> The location to apply the impulse at. </param>
	void applyImpulse(const Vector& impulse, const Vector& location);
	/// <summary> Apply an impulse to this object, changing its velocity by the same amount regardless of time since last frame. </summary>
	/// <param name="impulsex"> The impulse to be applied along the x-axis. </param>
	/// <param name="impulsey"> The impulse to be applied along the y-axis. </param>
	/// <param name="impulsez"> The impulse to be applied along the z-axis. </param>
	/// <param name="location"> The location to apply the impulse at. </param>
	void applyImpulse(const float& impulsex, const float& impulsey, const float& impulsez, const Vector& location);
	/// <summary> Set this object's moment of inertia. </summary>
	/// <param name="momi"> The new moment of inertia. </param>
	void setMomi(const Vector& momi);
	/// <summary> Set this object's moment of inertia. </summary>
	/// <param name="momix"> The the new moment of inertia about the x-axis. </param>
	/// <param name="momiy"> The the new moment of inertia about the y-axis. </param>
	/// <param name="momiz"> The the new moment of inertia about the z-axis. </param>
	void setMomi(const float& momix, const float& momiy, const float& momiz);
	/// <summary> Returns this object's location as a vector. </summary>
	Vector getLocation() const;
	/// <summary> Set this object's location. </summary>
	/// <param name="pos"> The new position of this object. </param>
	void setLocation(const Vector& pos);
	/// <summary> Set this object's location. </summary>
	/// <param name="x"> The new x position of this object. </param>
	/// <param name="y"> The new position of this object. </param>
	/// <param name="z"> The new position of this object. </param>
	void setLocation(const float& x, const float& y, const float& z);
	/// <summary> Returns this object's scale factors as a vector. </summary>
	Vector getScale() const;
	/// <summary> Set this object's scale factors. </summary>
	/// <param name="scale"> The new scaling of this object. </param>
	void setScale(const Vector& scale);
	/// <summary> Set this object's scale factors. </summary>
	/// <param name="xscale"> The new x scaling of this object. </param>
	/// <param name="yscale"> The new y scaling of this object. </param>
	/// <param name="zscale"> The new z scaling of this object. </param>
	void setScale(const float& xscale, const float& yscale, const float& zscale);
	/// <summary> Returns this object's rotation as a vector. </summary>
	Vector getRotation() const;
	/// <summary> Set this object's rotation. </summary>
	/// <param name="rotation"> The new rotation of this object. </param>
	void setRotation(const Vector& rotation);
	/// <summary> Set this object's rotation. </summary>
	/// <param name="xrotation"> The new x rotation of this object. </param>
	/// <param name="yrotation"> The new y rotation of this object. </param>
	/// <param name="zrotation"> The new z rotation of this object. </param>
	void setRotation(const float& xrotation, const float& yrotation, const float& zrotation);
protected:
	// The graphics shape to control the rendering of this object. Contains position, rotation, and scaling information.
	GraphicsShape* graphics;

	Particle();
};

