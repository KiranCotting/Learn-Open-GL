#include "Matrix.h"

Matrix::Matrix() {}

Matrix::Matrix(const float arr[]) {
	for (int i = 0; i < 16; ++i) {
		values[i] = arr[i];
	}
}

Matrix Matrix::identity() {
	float arr[] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
	return Matrix(arr);
}

const float& Matrix::getValue(const int& pos) const {
	return values[pos];
}

const float& Matrix::getValue(const int& pos1, const int& pos2) const {
	return values[pos1 * 4 + pos2];
}

const float* Matrix::getValues() const {
	return values;
}

Matrix Matrix::operator*(const Matrix& rhs) const {
	float arr[16] = {0};
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			int index = i * 4 + j;
			for (int k = 0; k < 4; ++k) {
				arr[index] += getValue(i, k) * rhs.getValue(k, j);
			}
		}
	}
	return Matrix(arr);
}

Vector Matrix::operator*(const Vector& rhs) const {
	float arr[4] = { 0 };
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			arr[i] += getValue(i, j) * rhs[j];
		}
	}
	return Vector(arr);
}

bool Matrix::operator==(const Matrix& rhs) const {
	for (int i = 0; i < 16; ++i) {
		if (values[i] != rhs.getValue(i)) {
			return false;
		}
	}
	return true;
}

bool Matrix::nearlyEquals(const Matrix& matrix, const float& tolerance) const {
	for (int i = 0; i < 16; ++i) {
		if (abs(values[i] - matrix.getValue(i)) > tolerance) {
			return false;
		}
	}
	return true;
}

Matrix Matrix::translate(const float& x, const float& y, const float& z) const {
	float arr[] = {
		1,0,0,x,
		0,1,0,y,
		0,0,1,z,
		0,0,0,1
	};
	return Matrix(arr) * *this;
}

Matrix Matrix::scale(const float& sx, const float& sy, const float& sz, const float& x, const float& y, const float& z) const {
	float arr[] = {
		sx,0,0,0,
		0,sy,0,0,
		0,0,sz,0,
		0,0,0,1
	};
	return (translate(x, y, z) * Matrix(arr)).translate(-x, -y, -z);
}

Matrix Matrix::rotateX(const float& theta, const bool& radians, const float& x, const float& y, const float& z) const {
	float t = theta;
	if (!radians) {
		t = t * (float) M_PI / 180;
	}
	return rotateXSC(sinf(t), cosf(t), x, y, z);
}

Matrix Matrix::rotateXSC(const float& sin, const float& cos, const float& x, const float& y, const float& z) const {
	float arr[] = {
		1,0,0,0,
		0,cos,-sin,0,
		0,sin,cos,0,
		0,0,0,1
	};
	return (translate(x, y, z) * Matrix(arr)).translate(-x, -y, -z);
}
Matrix Matrix::rotateY(const float& theta, const bool& radians, const float& x, const float& y, const float& z) const {
	float t = theta;
	if (!radians) {
		t = t * (float) M_PI / 180;
	}
	return rotateYSC(sinf(t), cosf(t), x, y, z);
}

Matrix Matrix::rotateYSC(const float& sin, const float& cos, const float& x, const float& y, const float& z) const {
	float arr[] = {
		cos,0,sin,0,
		0,1,0,0,
		-sin,0,cos,0,
		0,0,0,1
	};
	return (translate(x, y, z) * Matrix(arr)).translate(-x, -y, -z);
}

Matrix Matrix::rotateZ(const float& theta, const bool& radians, const float& x, const float& y, const float& z) const {
	float t = theta;
	if (!radians) {
		t = t * (float) M_PI / 180;
	}
	return rotateZSC(sinf(t), cosf(t), x, y, z);
}

Matrix Matrix::rotateZSC(const float& sin, const float& cos, const float& x, const float& y, const float& z) const {
	float arr[] = {
		cos,-sin,0,0,
		sin,cos,0,0,
		0,0,1,0,
		0,0,0,1
	};
	return (translate(x, y, z) * Matrix(arr)).translate(-x, -y, -z);
}

Matrix Matrix::rotate(const float& thetax, const float& thetay, const float& thetaz, const bool& radians, const float& x, const float& y, const float& z) const {
	float tx = thetax;
	float ty = thetay;
	float tz = thetaz;
	if (!radians) {
		tx = tx * (float) M_PI / 180;
		ty = ty * (float) M_PI / 180;
		tz = tz * (float) M_PI / 180;
	}
	return rotateSC(sinf(tx), cosf(tx), sinf(ty), cosf(ty), sinf(tz), cosf(tz), x, y, z);
}

Matrix Matrix::rotateSC(const float& sinx, const float& cosx, const float& siny, const float& cosy, const float& sinz, const float& cosz, const float& x, const float& y, const float& z) const {
	return this->rotateXSC(sinx, cosx, x, y, z).rotateYSC(siny, cosy, x, y, z).rotateZSC(sinz, cosz, x, y, z);
}