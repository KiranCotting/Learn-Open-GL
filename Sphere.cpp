#include "Sphere.h"
#include "Vector.h"
#include <ctime>
#include <iostream>

unsigned short Sphere::numVertices, * Sphere::numTriangleVertices, Sphere::numEdgeVertices;
float* Sphere::vertices, * Sphere::colors, * Sphere::edgeColors;
unsigned short** Sphere::triangles, * Sphere::edges;
unsigned int Sphere::vertexColorBuffer, * Sphere::trianglesBuffers, Sphere::edgesBuffer, Sphere::edgeColorsBuffer, Sphere::facesVAO, Sphere::edgesVAO;
bool Sphere::buffered = false, Sphere::initialized = false;
char Sphere::maxLOD = 5;

Sphere::Sphere(const float& x, const float& y, const float& z, const float& sx, const float& sy, const float& sz, const float& rx, const float& ry, const float& rz) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->sx = sx;
	this->sy = sy;
	this->sz = sz;
	this->rx = rx;
	this->ry = ry;
	this->rz = rz;
	this->currentLOD = 0;

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
		
		trianglesBuffers = new unsigned int[maxLOD + 1];
		numTriangleVertices = new unsigned short[maxLOD + 1];
		numTriangleVertices[0] = 24;

		triangles = new unsigned short*[maxLOD + 1];
		triangles[0] = new unsigned short[24]{
			0, 1, 2,
			0, 2, 3,
			0, 3, 4,
			0, 4, 1,
			5, 1, 4,
			5, 4, 3,
			5, 3, 2,
			5, 2, 1
		};

		createPoints(trianglesList, verticesList, verticesMap, numTriangleVertices, triangles);

		numVertices = (unsigned short) verticesMap.size();
		numEdgeVertices = 0;

		vertices = new float[verticesList.size() * 3];

		for (int i = 0; i < verticesList.size(); ++i) {
			vertices[i * 3] = verticesList.at(i).getX();
			vertices[i * 3 + 1] = verticesList.at(i).getY();
			vertices[i * 3 + 2] = verticesList.at(i).getZ();
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

void Sphere::createPoints(
	std::vector<Triangle>& trianglesList,
	std::vector<Vector>& verticesList,
	std::map<unsigned int,
	unsigned short>& verticesMap,
	unsigned short * const& numTriangleVertices,
	unsigned short * * const& triangles
) {
	for (int i = 0; i < maxLOD; ++i) {
		std::vector<Triangle> newTriangles;
		for (std::vector<Triangle>::iterator i = trianglesList.begin(); i < trianglesList.end(); ++i) {
			unsigned int ab = getMidPoint((*i).a, (*i).b, verticesList, verticesMap);
			unsigned int bc = getMidPoint((*i).b, (*i).c, verticesList, verticesMap);
			unsigned int ac = getMidPoint((*i).a, (*i).c, verticesList, verticesMap);
			newTriangles.push_back(Triangle((*i).a, ab, ac));
			newTriangles.push_back(Triangle((*i).b, bc, ab));
			newTriangles.push_back(Triangle((*i).c, ac, bc));
			newTriangles.push_back(Triangle(ab, bc, ac));
		}
		numTriangleVertices[i + 1] = (unsigned short) newTriangles.size() * 3;
		triangles[i + 1] = new unsigned short[newTriangles.size() * 3];
		int index = 0;
		for (std::vector<Triangle>::iterator iterator = newTriangles.begin(); iterator != newTriangles.end(); ++iterator) {
			triangles[i + 1][index] = (*iterator).a;
			triangles[i + 1][index + 1] = (*iterator).b;
			triangles[i + 1][index + 2] = (*iterator).c;
			index += 3;
		}
		trianglesList = newTriangles;
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

void Sphere::drawTriangles() {
	glDrawElements(GL_TRIANGLES, getNumTriangleVertices()[currentLOD], GL_UNSIGNED_SHORT, (void*)0);
}

char& Sphere::getMaxLOD() const { return maxLOD; }

unsigned short& Sphere::getNumVertices() const { return numVertices; }

unsigned short*& Sphere::getNumTriangleVertices() const { return numTriangleVertices; }

unsigned short& Sphere::getNumEdgeVertices() const { return numEdgeVertices; }

float*& Sphere::getVertices() const { return vertices; }

float*& Sphere::getColors() const { return colors; }

float*& Sphere::getEdgeColors() const { return edgeColors; }

unsigned short**& Sphere::getTriangles() const { return triangles; }

unsigned short*& Sphere::getEdges() const { return edges; }

unsigned int& Sphere::getVertexColorBuffer() const { return vertexColorBuffer; }

unsigned int*& Sphere::getTrianglesBuffers() const { return trianglesBuffers; }

unsigned int& Sphere::getEdgesBuffer() const { return edgesBuffer; }

unsigned int& Sphere::getEdgeColorsBuffer() const { return edgeColorsBuffer; }

unsigned int& Sphere::getFacesVAO() const { return facesVAO; }

unsigned int& Sphere::getEdgesVAO() const { return edgesVAO; }

bool& Sphere::getBuffered() const { return buffered; }