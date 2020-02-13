#include "Sphere.h"
#include "Vector.h"
#include <ctime>
#include <iostream>

unsigned short Sphere::numVertices, Sphere::numTriangleVertices, Sphere::numEdgeVertices;
float* Sphere::vertices, * Sphere::colors, * Sphere::edgeColors;
unsigned short* Sphere::triangles, * Sphere::edges;
unsigned int Sphere::vertexColorBuffer, Sphere::trianglesBuffer, Sphere::edgesBuffer, Sphere::edgeColorsBuffer, Sphere::facesVAO, Sphere::edgesVAO;
bool Sphere::buffered = false, Sphere::initialized = false;

Sphere::Sphere(const int& levelOfDetail, const float& x, const float& y, const float& z, const float& sx, const float& sy, const float& sz, const float& rx, const float& ry, const float& rz) {
	this->levelOfDetail = levelOfDetail;
	this->x = x;
	this->y = y;
	this->z = z;
	this->sx = sx;
	this->sy = sy;
	this->sz = sz;
	this->rx = rx;
	this->ry = ry;
	this->rz = rz;

	if (!initialized) {
		// Start by defining the octahedron.
		// It has 6 vertices (represented by vectors here)
		std::vector<Vector> verticesList = {
			Vector(0.0f, 1.0f, 0.0f),
			Vector(0.0f, 0.0f, 1.0f),
			Vector(1.0f, 0.0f, 0.0f),
			Vector(0.0f, 0.0f, -1.0f),
			Vector(-1.0f, 0.0f, 0.0f),
			Vector(0.0f, -1.0f, 0.0f)
		};

		std::map<unsigned int, unsigned short> verticesMap = {
			{(unsigned int)0, 0},
			{(unsigned short)1 << 16 | (unsigned int)1, 1},
			{(unsigned short)2 << 16 | (unsigned int)2, 2},
			{(unsigned short)3 << 16 | (unsigned int)3, 3},
			{(unsigned short)4 << 16 | (unsigned int)4, 4},
			{(unsigned short)5 << 16 | (unsigned int)5, 5}
		};

		std::vector<Triangle> trianglesList = {
			Triangle(0, 1, 2),
			Triangle(0, 2, 3),
			Triangle(0, 3, 4),
			Triangle(0, 4, 1),
			Triangle(5, 1, 4),
			Triangle(5, 4, 3),
			Triangle(5, 3, 2),
			Triangle(5, 2, 1),
		};

		createPoints(trianglesList, verticesList, verticesMap, levelOfDetail);

		numVertices = (unsigned short) verticesMap.size();
		numTriangleVertices = (unsigned short) trianglesList.size() * 3;
		numEdgeVertices = 0;

		vertices = new float[verticesList.size() * 3];

		int index = 0;
		for (std::vector<Vector>::iterator i = verticesList.begin(); i != verticesList.end(); ++i) {
			vertices[index] = (*i).getX();
			vertices[index + 1] = (*i).getY();
			vertices[index + 2] = (*i).getZ();
			index += 3;
		}

		triangles = new unsigned short[trianglesList.size() * 3];

		index = 0;
		for (std::vector<Triangle>::iterator i = trianglesList.begin(); i != trianglesList.end(); ++i) {
			triangles[index] = (*i).a;
			triangles[index + 1] = (*i).b;
			triangles[index + 2] = (*i).c;
			index += 3;
		}

		colors = new float[numVertices * 4];

		srand((unsigned int)time(0));

		for (int i = 0; i < numVertices * 4; i += 4) {
			colors[i] = rand() % 100 / 100.0f;
			colors[i + 1] = rand() % 100 / 100.0f;
			colors[i + 2] = rand() % 100 / 100.0f;
			colors[i + 3] = 0.0f;
		}

		initialized = true;
	}
}

void Sphere::createPoints(std::vector<Triangle>& triangles, std::vector<Vector>& verticesList, std::map<unsigned int, unsigned short>& verticesMap, const char& recursion) {
	for (int i = 0; i < recursion; ++i) {
		std::vector<Triangle> newTriangles;
		for (std::vector<Triangle>::iterator i = triangles.begin(); i < triangles.end(); ++i) {
			unsigned int ab = getMidPoint((*i).a, (*i).b, verticesList, verticesMap);
			unsigned int bc = getMidPoint((*i).b, (*i).c, verticesList, verticesMap);
			unsigned int ac = getMidPoint((*i).a, (*i).c, verticesList, verticesMap);
			newTriangles.push_back(Triangle((*i).a, ab, ac));
			newTriangles.push_back(Triangle((*i).b, bc, ab));
			newTriangles.push_back(Triangle((*i).c, ac, bc));
			newTriangles.push_back(Triangle(ab, bc, ac));
		}
		triangles = newTriangles;
	}
}

unsigned short Sphere::getMidPoint(unsigned short a, unsigned short b, std::vector<Vector>& verticesList, std::map<unsigned int, unsigned short>& verticesMap) {
	unsigned short lower = a < b ? a : b;
	unsigned short higher = a >= b ? a : b;
	unsigned int key = lower << 16 | higher;
	std::map<unsigned int, unsigned short>::iterator result = verticesMap.find(key);
	if (result == verticesMap.end()) {
		verticesList.push_back(~(verticesList[a] + verticesList[b]));
		verticesMap.insert(std::pair<unsigned int, unsigned short>(key, verticesList.size() - 1));
		return (unsigned short) verticesList.size() - 1;
	}
	else {
		return (*result).second;
	}
}

void Sphere::render(const Matrix& projection, const Matrix& view) {
	GraphicsShape::render(projection, view);
	Vector position(x, y, z);
	position = view * position;
	levelOfDetail = (char) -100 / position.getZ();
	if (levelOfDetail > 5) {
		levelOfDetail = 5;
	} else if (levelOfDetail < 0) {
		levelOfDetail = 0;
	}
}

void Sphere::drawTriangles() {
	glDrawElements(GL_TRIANGLES, numTriangleVertices, GL_UNSIGNED_SHORT, (void*)0);
}

unsigned short& Sphere::getNumVertices() const { return numVertices; }

unsigned short& Sphere::getNumTriangleVertices() const { return numTriangleVertices; }

unsigned short& Sphere::getNumEdgeVertices() const { return numEdgeVertices; }

float*& Sphere::getVertices() const { return vertices; }

float*& Sphere::getColors() const { return colors; }

float*& Sphere::getEdgeColors() const { return edgeColors; }

unsigned short*& Sphere::getTriangles() const { return triangles; }

unsigned short*& Sphere::getEdges() const { return edges; }

unsigned int& Sphere::getVertexColorBuffer() const { return vertexColorBuffer; }

unsigned int& Sphere::getTrianglesBuffer() const { return trianglesBuffer; }

unsigned int& Sphere::getEdgesBuffer() const { return edgesBuffer; }

unsigned int& Sphere::getEdgeColorsBuffer() const { return edgeColorsBuffer; }

unsigned int& Sphere::getFacesVAO() const { return facesVAO; }

unsigned int& Sphere::getEdgesVAO() const { return edgesVAO; }

bool& Sphere::getBuffered() const { return buffered; }