#pragma once
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <cmath>
#include "Vector.h"

/// <summary>
/// A 4x4 matrix of float values, used to represent 3D transformations.
/// </summary>
class Matrix {
private:
	float values[16] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
public:
	Matrix();
	/// <summary> This constructor initializes the array values to <paramref name="arr"/> </summary>
	/// <param name="arr"> An array of 16 float values, specified by row. </param>
	Matrix(const float arr[]);

	/// <summary> Returns the identity matrix. </summary>
	static Matrix identity();

	/// <summary> Gets a single value from the matrix. </summary>
	/// <param name="pos"> The position of the value to get. </param>
	const float& getValue(const int& pos) const;

	/// <summary> Gets a single value from the matrix. </summary>
	/// <param name="row"> The row of the value to get. </param>
	/// <param name="col"> The column of the value to get. </param>
	const float& getValue(const int& row, const int& col) const;

	/// <summary> Gets the underlying matrix values. </summary>
	const float* getValues() const;

	/// <summary> Multiplies two matrices together. </summary>
	Matrix operator*(const Matrix&) const;

	/// <summary> Multiplies this matrix onto a vector. </summary>
	Vector operator*(const Vector&) const;

	/// <summary> Checks if two matrices are equivalent. </summary>
	bool operator==(const Matrix&) const;

	/// <summary> Checks if two matrices are nearly equivalent. </summary>
	/// <param name="matrix"> The matrix to check against. </param>
	/// <param name="toelrance"> The amount the values can be off by and still be considered equal. </param>
	bool nearlyEquals(const Matrix& matrix, const float& tolerance) const;

	/// <summary> Returns this matrix translated by <paramref name="x"/>, <paramref name="y"/>, <paramref name="z"/> </summary>
	/// <param name="x"> The x value to translate by. </param>
	/// <param name="y"> The y value to translate by. </param>
	/// <param name="z"> The z value to translate by. </param>
	Matrix translate(const float& x, const float& y, const float& z) const;

	/// <summary> 
	/// Returns this matrix scaled by <paramref name="sx"/>, <paramref name="sy"/>, <paramref name="sz"/>
	/// around the point <paramref name="x"/>, <paramref name="y"/>, <paramref name="z"/>
	/// </summary>
	/// <param name="sx"> The scale factor along the x-axis. </param>
	/// <param name="sy"> The scale factor along the y-axis. </param>
	/// <param name="sz"> The scale factor along the z-axis. </param>
	/// <param name="x"> The x value to scale around. </param>
	/// <param name="y"> The y value to scale around. </param>
	/// <param name="z"> The z value to scale around. </param>
	Matrix scale(const float& sx, const float& sy, const float& sz, const float& x = 0, const float& y = 0, const float& z = 0) const;

	/// <summary> Returns this matrix rotated around the x-axis by <paramref name="theta"/> around the point <paramref name="x"/>, <paramref name="y"/>, <paramref name="z"/> </summary>
	/// <param name="theta"> The amount in RADIANS to rotate. </param>
	/// <param name="x"> The x value to rotate around. </param>
	/// <param name="y"> The y value to rotate around. </param>
	/// <param name="z"> The z value to rotate around. </param>
	/// <param name="radians"> Whether the rotation is in radians or degrees. </param>
	Matrix rotateX(const float& theta, const bool& radians = false, const float& x = 0, const float& y = 0, const float& z = 0) const;

	/// <summary> 
	/// Returns this matrix rotated around the x-axis by <paramref name="sin"/>, <paramref name="cos"/> around the point <paramref name="x"/>, <paramref name="y"/>, <paramref name="z"/>
	/// This function is best used to avoid re-calculating sin and cos values when rotating multiple matrices at once.
	/// </summary>
	/// <param name="sin"> The sin of the angle to rotate by. </param>
	/// <param name="cos"> The cos of the angle to rotate by. </param>
	/// <param name="x"> The x value to rotate around. </param>
	/// <param name="y"> The y value to rotate around. </param>
	/// <param name="z"> The z value to rotate around. </param>
	Matrix rotateXSC(const float& sin, const float& cos, const float& x = 0, const float& y = 0, const float& z = 0) const;

	/// <summary> Returns this matrix rotated around the y-axis by <paramref name="theta"/> around the point <paramref name="x"/>, <paramref name="y"/>, <paramref name="z"/> </summary>
	/// <param name="theta"> The amount in RADIANS to rotate. </param>
	/// <param name="x"> The x value to rotate around. </param>
	/// <param name="y"> The y value to rotate around. </param>
	/// <param name="z"> The z value to rotate around. </param>
	/// <param name="radians"> Whether the rotation is in radians or degrees. </param>
	Matrix rotateY(const float& theta, const bool& radians = false, const float& x = 0, const float& y = 0, const float& z = 0) const;

	/// <summary> 
	/// Returns this matrix rotated around the y-axis by <paramref name="sin"/>, <paramref name="cos"/> around the point <paramref name="x"/>, <paramref name="y"/>, <paramref name="z"/>
	/// This function is best used to avoid re-calculating sin and cos values when rotating multiple matrices at once.
	/// </summary>
	/// <param name="sin"> The sin of the angle to rotate by. </param>
	/// <param name="cos"> The cos of the angle to rotate by. </param>
	/// <param name="x"> The x value to rotate around. </param>
	/// <param name="y"> The y value to rotate around. </param>
	/// <param name="z"> The z value to rotate around. </param>
	Matrix rotateYSC(const float& sin, const float& cos, const float& x = 0, const float& y = 0, const float& z = 0) const;

	/// <summary> Returns this matrix rotated around the z-axis by <paramref name="theta"/> around the point <paramref name="x"/>, <paramref name="y"/>, <paramref name="z"/> </summary>
	/// <param name="theta"> The amount in RADIANS to rotate. </param>
	/// <param name="x"> The x value to rotate around. </param>
	/// <param name="y"> The y value to rotate around. </param>
	/// <param name="z"> The z value to rotate around. </param>
	/// <param name="radians"> Whether the rotation is in radians or degrees. </param>
	Matrix rotateZ(const float& theta, const bool& radians = false, const float& x = 0, const float& y = 0, const float& z = 0) const;

	/// <summary>
	/// Returns this matrix rotated around the z-axis by <paramref name="sin"/>, <paramref name="cos"/> around the point <paramref name="x"/>, <paramref name="y"/>, <paramref name="z"/>
	/// This function is best used to avoid re-calculating sin and cos values when rotating multiple matrices at once.
	/// </summary>
	/// <param name="sin"> The sin of the angle to rotate by. </param>
	/// <param name="cos"> The cos of the angle to rotate by. </param>
	/// <param name="x"> The x value to rotate around. </param>
	/// <param name="y"> The y value to rotate around. </param>
	/// <param name="z"> The z value to rotate around. </param>
	Matrix rotateZSC(const float& sin, const float& cos, const float& x = 0, const float& y = 0, const float& z = 0) const;

	/// <summary> 
	/// Returns this matrix rotated by <paramref name="thetax"/> around x-axis,
	/// <paramref name="thetay"/> around y-axis,
	/// <paramref name="thetaz"/> around z-axis,
	/// around the point <paramref name="x"/>, <paramref name="y"/>, <paramref name="z"/>
	/// This function is best used to avoid re-calculating sin and cos values when rotating multiple matrices at once.
	/// </summary>
	/// <param name="thetax"> The amount in RADIANS to rotate around the x-axis. </param>
	/// <param name="thetay"> The amount in RADIANS to rotate around the y-axis. </param>
	/// <param name="thetaz"> The amount in RADIANS to rotate around the z-axis. </param>
	/// <param name="x"> The x value to rotate around. </param>
	/// <param name="y"> The y value to rotate around. </param>
	/// <param name="z"> The z value to rotate around. </param>
	/// <param name="radians"> Whether the rotation is in radians or degrees. </param>
	Matrix rotate(const float& thetax, const float& thetay, const float& thetaz, const bool& radians = false, const float& x = 0, const float& y = 0, const float& z = 0) const;

	/// <summary> 
	/// Returns this matrix rotated by <paramref name="sinx"/>,  <paramref name="cosx"/> around x-axis,
	/// <paramref name="siny"/>, <paramref name="cosy"/> around y-axis,
	/// <paramref name="sinz"/>, <paramref name="cosz"/> around z-axis,
	/// around the point <paramref name="x"/>, <paramref name="y"/>, <paramref name="z"/>
	/// This function is best used to avoid re-calculating sin and cos values when rotating multiple matrices at once.
	/// </summary>
	/// <param name="sinx"> The sin of the angle to rotate around the x-axis by. </param>
	/// <param name="cosx"> The cos of the angle to rotate around the x-axis by. </param>
	/// <param name="siny"> The sin of the angle to rotate around the y-axis by. </param>
	/// <param name="cosy"> The cos of the angle to rotate around the y-axis by. </param>
	/// <param name="sinz"> The sin of the angle to rotate around the z-axis by. </param>
	/// <param name="cosz"> The cos of the angle to rotate around the z-axis by. </param>
	/// <param name="x"> The x value to rotate around. </param>
	/// <param name="y"> The y value to rotate around. </param>
	/// <param name="z"> The z value to rotate around. </param>
	Matrix rotateSC(const float& sinx, const float& cosx, const float& siny, const float& cosy, const float& sinz, const float& cosz, const float& x = 0, const float& y = 0, const float& z = 0) const;
};