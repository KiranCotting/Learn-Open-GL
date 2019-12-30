#include "Sphere.h"
#include "Vector.h"

Sphere::Sphere(const int& levelOfDetail, const float& x, const float& y, const float& z, const float& sx, const float& sy, const float& sz, const float& rx, const float& ry, const float& rz) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->sx = sx;
	this->sy = sy;
	this->sz = sz;
	this->rx = rx;
	this->ry = ry;
	this->rz = rz;

	// Start by defining the octahedron.
		// It has 6 vertices (represented by vectors here)
	RecursiveVector* vectors = new RecursiveVector[8 * levelOfDetail] {
			RecursiveVector(0.0f, 1.0f, 0.0f),
			RecursiveVector(0.0f, 0.0f, 1.0f),
			RecursiveVector(1.0f, 0.0f, 0.0f),
			RecursiveVector(0.0f, 0.0f, -1.0f),
			RecursiveVector(-1.0f, 0.0f, 0.0f),
			RecursiveVector(0.0f, -1.0f, 0.0f)
	};

	// And it has 8 triangles, which store the indices of their vertices rather than the vertices themselves.
	Triangle* triangles = new Triangle[8 * pow(3, levelOfDetail - 1)] {
			new Triangle{&vectors[0], &vectors[1], &vectors[2]},
			new Triangle{&vectors[0], &vectors[2], &vectors[3]},
			new Triangle{&vectors[0], &vectors[3], &vectors[4]},
			new Triangle{&vectors[0], &vectors[4], &vectors[1]},
			new Triangle{&vectors[5], &vectors[2], &vectors[1]},
			new Triangle{&vectors[5], &vectors[3], &vectors[2]},
			new Triangle{&vectors[5], &vectors[4], &vectors[3]},
			new Triangle{&vectors[5], &vectors[1], &vectors[4]}
	};
}

void Sphere::drawTriangles() {
	glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_SHORT, (void*)0);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_SHORT, (void*)20);
}

void Sphere::recurse(const Triangle& triangle) {

}