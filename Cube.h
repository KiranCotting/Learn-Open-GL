#pragma once
#include "GraphicsShape.h"

/// <summary> A child of GraphicsShape, to represent any Cube. </summary>
class Cube : public GraphicsShape {
public:
	/// <summary> Cube constructor. </summary>
	/// <param name="x"> The x-coord of this cube. </param>
	/// <param name="y"> The y-coord of this cube. </param>
	/// <param name="z"> The z-coord of this cube. </param>
	/// <param name="sx"> The x-scale of this cube. </param>
	/// <param name="sy"> The y-scale of this cube. </param>
	/// <param name="sz"> The z-scale of this cube. </param>
	/// <param name="rx"> The x-rotation of this cube, in degrees. </param>
	/// <param name="ry"> The y-rotation of this cube, in degrees. </param>
	/// <param name="rz"> The z-rotation of this cube, in degrees. </param>
	Cube(const float& x = 0, const float& y = 0, const float& z = 0, const float& sx = 0, const float& sy = 0, const float& sz = 0, const float& rx = 0, const float& ry = 0, const float& rz = 0);
	void drawTriangles() override;
};

