#include "Vector.h"

Vector::Vector(const float arr[]) {
	for (int i = 0; i < 4; ++i) {
		values[i] = arr[i];
	}
}

Vector::Vector(const float& x, const float& y, const float& z) {
	values[0] = x;
	values[1] = y;
	values[2] = z;
}

Vector Vector::operator+(const Vector& rhs) const {
	float arr[] = {
		values[0] + rhs.values[0],
		values[1] + rhs.values[1],
		values[2] + rhs.values[2],
	};
	return Vector(arr);
}

Vector& Vector::operator+=(const Vector& rhs) {
	values[0] += rhs.values[0];
	values[1] += rhs.values[1];
	values[2] += rhs.values[2];
	return *this;
}

Vector Vector::operator-(const Vector& rhs) const {
	return *this + -rhs;
}

Vector& Vector::operator-=(const Vector& rhs) {
	return *this += -rhs;
}

Vector Vector::operator&(const Vector& rhs) const {
	float arr[] = {
		values[0] * rhs.values[0],
		values[1] * rhs.values[1],
		values[2] * rhs.values[2]
	};
	return Vector(arr);
}

Vector& Vector::operator&=(const Vector& rhs) {
	values[0] *= rhs.values[0];
	values[1] *= rhs.values[1];
	values[2] *= rhs.values[2];
	return *this;
}

Vector Vector::operator/(const Vector& rhs) const {
	float arr[] = {
		values[0] / rhs.values[0],
		values[1] / rhs.values[1],
		values[2] / rhs.values[2]
	};
	return Vector(arr);
}

Vector& Vector::operator/=(const Vector& rhs) {
	values[0] /= rhs.values[0];
	values[1] /= rhs.values[1];
	values[2] /= rhs.values[2];
	return *this;
}

Vector Vector::operator*(const float& rhs) const {
	float arr[] = {
		values[0] * rhs,
		values[1] * rhs,
		values[2] * rhs
	};
	return Vector(arr);
}

Vector& Vector::operator*=(const float& rhs) {
	values[0] *= rhs;
	values[1] *= rhs;
	values[2] *= rhs;
	return *this;
}

Vector Vector::operator/(const float& rhs) const {
	return *this * (1 / rhs);
}

Vector& Vector::operator/=(const float& rhs) {
	values[0] /= rhs;
	values[1] /= rhs;
	values[2] /= rhs;
	return *this;
}

float Vector::operator*(const Vector& rhs) const {
	float dot = 0;
	for (int i = 0; i < 3; ++i) {
		dot += values[i] * rhs.values[i];
	}
	return dot;
}

Vector Vector::operator%(const Vector& rhs) const {
	float arr[] = {
		values[1] * rhs.values[2] - values[2] * rhs.values[1],
		values[2] * rhs.values[0] - values[0] * rhs.values[2],
		values[0] * rhs.values[1] - values[1] * rhs.values[0]
	};
	return Vector(arr);
}

Vector& Vector::operator%=(const Vector& rhs) {
	values[0] = values[1] * rhs.values[2] - values[2] * rhs.values[1];
	values[1] = values[2] * rhs.values[0] - values[0] * rhs.values[2];
	values[2] = values[0] * rhs.values[1] - values[1] * rhs.values[0];
	return *this;
}

Vector Vector::operator~() const {
	const float len = mag();
	float arr[] = {
		values[0] / len,
		values[1] / len,
		values[2] / len
	};
	return Vector(arr);
}

Vector Vector::operator-() const {
	float arr[] = {
		-values[0],
		-values[1],
		-values[2]
	};
	return Vector(arr);
}

float Vector::operator[](const int& i) const {
	return values[i];
}

float Vector::mag() const {
	return sqrtf(values[0] * values[0] + values[1] * values[1] + values[2] * values[2]);
}

float Vector::mag2() const {
	return values[0] * values[0] + values[1] * values[1] + values[2] * values[2];
}

void Vector::normalize() {
	const float len = mag();
	values[0] /= len;
	values[1] /= len;
	values[2] /= len;
}
/// <summary> Gets the underlying vector values. </summary>
const float* Vector::getValues() const {
	return values;
}
/// <summary> Gets the x component of the vector. </summary>
float Vector::getX() const {
	return values[0];
}
/// <summary> Gets the y component of the vector. </summary>
float Vector::getY() const {
	return values[1];
}
/// <summary> Gets the z component of the vector. </summary>
float Vector::getZ() const {
	return values[2];
}