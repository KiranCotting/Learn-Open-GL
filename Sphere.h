#pragma once
#include "GraphicsShape.h"

/// <summary> A child of GraphicsShape, to represent any Cube. </summary>
class Sphere : public GraphicsShape {
public:
	/// <summary> Cube constructor. </summary>
	/// <param name="levelOfDetail"> The level of detail to use when creating this sphere. Higher is better detail, but less efficient. </param>
	/// <param name="x"> The x-coord of this sphere. </param>
	/// <param name="y"> The y-coord of this sphere. </param>
	/// <param name="z"> The z-coord of this sphere. </param>
	/// <param name="sx"> The x-scale of this sphere. </param>
	/// <param name="sy"> The y-scale of this sphere. </param>
	/// <param name="sz"> The z-scale of this sphere. </param>
	/// <param name="rx"> The x-rotation of this sphere, in degrees. </param>
	/// <param name="ry"> The y-rotation of this sphere, in degrees. </param>
	/// <param name="rz"> The z-rotation of this sphere, in degrees. </param>
	Sphere(const int& levelOfDetail = 1, const float& x = 0, const float& y = 0, const float& z = 0, const float& sx = 0, const float& sy = 0, const float& sz = 0, const float& rx = 0, const float& ry = 0, const float& rz = 0);
	void drawTriangles() override;
private:
	struct Triangle {
		RecursiveVector* pointA = nullptr;
		RecursiveVector* pointB = nullptr;
		RecursiveVector* pointC = nullptr;
	};

	class RecursiveVector : Vector {
		RecursiveVector* parentA = nullptr;
		RecursiveVector* parentB = nullptr;
	public:
		RecursiveVector() = default;

		RecursiveVector(const float& x, const float& y, const float& z) {
			Vector(x, y, z);
		}
	};

	void recurse(const Triangle& triangle);
};