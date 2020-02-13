#pragma once
#include <cmath>
class Vector {
private:
	float values[4] = { 0,0,0,1 };
public:
	Vector() = default;
	/// <summary> Creates a new vector from the values in <paramref name="arr"/> </summary>
	/// <param name="arr"> The 3 values to initialize the vector with. </param>
	Vector(const float arr[]);
	/// <summary> Creates a new vector from x,y,z values. </summary>
	/// <param name="x"> The x component of the vector. </param>
	/// <param name="y"> The y component of the vector. </param>
	/// <param name="z"> The x component of the vector. </param>
	Vector(const float& x, const float& y, const float& z);
	/// <summary> Pairwise addition. </summary>
	Vector operator+(const Vector&) const;
	/// <summary> Pairwise incremental addition. </summary>
	Vector& operator+=(const Vector&);
	/// <summary> Pairwise subtraction. </summary>
	Vector operator-(const Vector&) const;
	/// <summary> Pairwise incremental subtraction. </summary>
	Vector& operator-=(const Vector&);
	/// <summary> Pairwise multiplication. </summary>
	Vector operator&(const Vector&) const;
	/// <summary> Pairwise incremental multiplication. </summary>
	Vector& operator&=(const Vector&);
	/// <summary> Pairwise division. </summary>
	Vector operator/(const Vector&) const;
	/// <summary> Pairwise incremental division. </summary>
	Vector& operator/=(const Vector&);
	/// <summary> Scalar multiplication. </summary>
	Vector operator*(const float&) const;
	/// <summary> Scalar incremental multiplication. </summary>
	Vector& operator*=(const float&);
	/// <summary> Scalar division. </summary>
	Vector operator/(const float&) const;
	/// <summary> Scalar incremental division. </summary>
	Vector& operator/=(const float&);
	/// <summary> Dot product. </summary>
	float operator*(const Vector&) const;
	/// <summary> Cross product. </summary>
	Vector operator%(const Vector&) const;
	/// <summary> Incremental cross product. </summary>
	Vector& operator%=(const Vector&);
	/// <summary> Normalized vector. </summary>
	Vector operator~() const;
	/// <summary> Negated vector. </summary>
	Vector operator-() const;
	/// <summary> Value accessor. </summary>
	float operator[](const int&) const;
	/// <summary> Vector equality. </summary>
	bool operator==(const Vector&) const;
	/// <summary> Vector equality within tolerance. </summary>
	/// <param name="rhs"> The other Vector to check equality against. </param>
	/// <param name="tolerance"> How far apart two values can be to be considered equal. </param>
	bool nearlyEquals(const Vector& rhs, const float& tolerance) const;
	/// <summary> Magnitude. </summary>
	float mag() const;
	/// <summary> Square magnitude. </summary>
	float mag2() const;
	/// <summary> Normalizes this vector. </summary>
	void normalize();
	/// <summary> Gets the underlying vector values. </summary>
	const float* getValues() const;
	/// <summary> Gets the x component of the vector. </summary>
	float getX() const;
	/// <summary> Gets the y component of the vector. </summary>
	float getY() const;
	/// <summary> Gets the z component of the vector. </summary>
	float getZ() const;
};