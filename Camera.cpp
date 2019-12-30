#include "Camera.h"

Matrix Camera::getView() const {
	return Matrix(view);
}

Matrix Camera::getProjection() const {
	return Matrix(projection);
}

Matrix Camera::ortho(const float& left, const float& right, const float& bottom, const float& top, const float& near, const float& far) {
	float arr[] = {
		2 / (right - left), 0, 0, -(right + left) / (right - left),
		0, 2 / (top - bottom), 0, -(top + bottom) / (top - bottom),
		0, 0, -2 / (far - near), -(far + near) / (far - near),
		0, 0, 0, 1
	};
	projection = Matrix(arr);
	return Matrix(projection);
}

Matrix Camera::frustum(const float& left, const float& right, const float& bottom, const float& top, const float& near, const float& far) {
	float arr[] = {
		2 * near / (right - left), 0, (right + left) / (right - left), 0,
		0, 2 * near / (top - bottom), (top + bottom) / (top - bottom), 0,
		0, 0, -(far + near) / (far - near), -2 * far * near / (far - near),
		0, 0, -1, 0
	};
	projection = Matrix(arr);
	return Matrix(projection);
}

Matrix Camera::lookAt(const Vector& position, const Vector& target, const Vector& vup) {
	Vector n = ~(position - target);
	Vector u = ~(vup % n);
	Vector v = n % u;
	float arr[] = {
		u[0], u[1], u[2], 0,
		v[0], v[1], v[2], 0,
		n[0], n[1], n[2], 0,
		0, 0, 0, 1
	};
	view = Matrix(arr) * Matrix::identity().translate(-position[0], -position[1], -position[2]);
	return Matrix(view);
}

Matrix Camera::viewPoint(const Vector& position, const Vector& vnormal, const Vector& vup) {
	Vector n = ~(-vnormal);
	Vector u = ~(vup % n);
	Vector v = n % u;
	float arr[] = {
		u[0], u[1], u[2], 0,
		v[0], v[1], v[2], 0,
		n[0], n[1], n[2], 0,
		0, 0, 0, 1
	};
	view = Matrix(arr) * Matrix::identity().translate(-position[0], -position[1], -position[2]);
	return Matrix(view);
}