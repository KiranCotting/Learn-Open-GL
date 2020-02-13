#include "Cube.h"

unsigned short Cube::numVertices, Cube::numTriangleVertices, Cube::numEdgeVertices;
float* Cube::vertices, * Cube::colors, * Cube::edgeColors;
unsigned short* Cube::triangles, * Cube::edges;
unsigned int Cube::vertexColorBuffer, Cube::trianglesBuffer, Cube::edgesBuffer, Cube::edgeColorsBuffer, Cube::facesVAO, Cube::edgesVAO;
bool Cube::buffered = false, Cube::initialized = false;

Cube::Cube(const float& x, const float& y, const float& z, const float& sx, const float& sy, const float& sz, const float& rx, const float& ry, const float& rz) {
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
		numVertices = 8;
		numTriangleVertices = 22;
		numEdgeVertices = 24;
		vertices = new float[numVertices * 3]{
			-0.5, -0.5, -0.5,
			0.5, -0.5, -0.5,
			-0.5, 0.5, -0.5,
			-0.5, -0.5, 0.5,
			0.5, 0.5, -0.5,
			0.5, -0.5, 0.5,
			-0.5, 0.5, 0.5,
			0.5, 0.5, 0.5
		};
		colors = new float[numVertices * 4]{
			0, 0, 0, 1, // black
			1, 0, 0, 1, // red
			0, 1, 0, 1, // green
			0, 0, 1, 1, // blue
			1, 1, 0, 1, // yellow
			1, 0, 1, 1, // magenta
			0, 1, 1, 1, // cyan
			1, 1, 1, 1 // white
		};
		edges = new unsigned short[numEdgeVertices] {
			0, 1,
				1, 4,
				4, 2,
				2, 0,
				3, 6,
				6, 7,
				7, 5,
				5, 3,
				0, 3,
				1, 5,
				2, 6,
				4, 7
		};
		edgeColors = new float[numVertices * 4]{
			0, 0, 0, 1, // black
			0, 0, 0, 1, // black
			0, 0, 0, 1, // black
			0, 0, 0, 1, // black
			0, 0, 0, 1, // black
			0, 0, 0, 1, // black
			0, 0, 0, 1, // black
			0, 0, 0, 1 // black
		};
		triangles = new unsigned short[numTriangleVertices] {
			0, 1, 3, 5, // bottom
				6, 7, // front
				2, 4, // top
				0, 1, // back
				1, 4, 7, 1, 7, 5, // right
				0, 3, 6, 0, 6, 2 // left
		};
		initialized = false;
	}
}

void Cube::drawTriangles() {
	glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_SHORT, (void*)0);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_SHORT, (void*)20);
}

unsigned short& Cube::getNumVertices() const { return numVertices; }

unsigned short& Cube::getNumTriangleVertices() const { return numTriangleVertices; }

unsigned short& Cube::getNumEdgeVertices() const { return numEdgeVertices; }

float*& Cube::getVertices() const { return vertices; }

float*& Cube::getColors() const { return colors; }

float*& Cube::getEdgeColors() const { return edgeColors; }

unsigned short*& Cube::getTriangles() const { return triangles; }

unsigned short*& Cube::getEdges() const { return edges; }

unsigned int& Cube::getVertexColorBuffer() const { return vertexColorBuffer; }

unsigned int& Cube::getTrianglesBuffer() const { return trianglesBuffer; }

unsigned int& Cube::getEdgesBuffer() const { return edgesBuffer; }

unsigned int& Cube::getEdgeColorsBuffer() const { return edgeColorsBuffer; }

unsigned int& Cube::getFacesVAO() const { return facesVAO; }

unsigned int& Cube::getEdgesVAO() const { return edgesVAO; }

bool& Cube::getBuffered() const { return buffered; }