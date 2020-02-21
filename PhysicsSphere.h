#pragma once
#include "Sphere.h"
#include "Particle.h"

class PhysicsSphere : public Particle
{
public:
	/// <summary> PhysicsSphere constructor. </summary>
	/// <param name="x"> The x-coord of this sphere. </param>
	/// <param name="y"> The y-coord of this sphere. </param>
	/// <param name="z"> The z-coord of this sphere. </param>
	/// <param name="r"> The radius of this sphere. </param>
	PhysicsSphere(const float& x = 0, const float& y = 0, const float& z = 0, const float& r = 1);

	const float& getRadius() const;
	void setRadius(const float& radius);
private:
	float radius;
};

