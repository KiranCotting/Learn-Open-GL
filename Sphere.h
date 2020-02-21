#pragma once
#include "GraphicsShape.h"
#include <map>
#include <vector>

/// <summary> A child of GraphicsShape, to represent any Sphere. </summary>
class Sphere : public GraphicsShape {
public:
	/// <summary> Sphere constructor. </summary>
	/// <param name="x"> The x-coord of this sphere. </param>
	/// <param name="y"> The y-coord of this sphere. </param>
	/// <param name="z"> The z-coord of this sphere. </param>
	/// <param name="sx"> The x-scale of this sphere. </param>
	/// <param name="sy"> The y-scale of this sphere. </param>
	/// <param name="sz"> The z-scale of this sphere. </param>
	/// <param name="rx"> The x-rotation of this sphere, in radians. </param>
	/// <param name="ry"> The y-rotation of this sphere, in radians. </param>
	/// <param name="rz"> The z-rotation of this sphere, in radians. </param>
	Sphere(const float& x = 0, const float& y = 0, const float& z = 0, const float& sx = 1, const float& sy = 1, const float& sz = 1, const float& rx = 0, const float& ry = 0, const float& rz = 0);

	void drawTriangles() override;
private:
	struct Triangle {
		unsigned short a, b, c;
		Triangle(unsigned short a, unsigned short b, unsigned short c) : a(a), b(b), c(c) {}
	};

	static unsigned short numVertices, * numTriangleVertices, numEdgeVertices;
	static float* vertices, * colors, * edgeColors;
	static unsigned short** triangles, * edges;
	static unsigned int vertexColorBuffer, * trianglesBuffers, edgesBuffer, edgeColorsBuffer, facesVAO, edgesVAO;
	static bool buffered, initialized;
	static char maxLOD;

	void createPoints(
		std::vector<Triangle>&,
		std::vector<Vector>&,
		std::map<unsigned int,
		unsigned short>&,
		unsigned short * const&,
		unsigned short * * const&
	);

	char& getMaxLOD() const override;

	unsigned short getMidPoint(unsigned short a, unsigned short b, std::vector<Vector>&, std::map<unsigned int, unsigned short>&);

	unsigned short& getNumVertices() const override;

	unsigned short*& getNumTriangleVertices() const override;

	unsigned short& getNumEdgeVertices() const override;

	float*& getVertices() const override;

	float*& getColors() const override;

	float*& getEdgeColors() const override;

	unsigned short**& getTriangles() const override;

	unsigned short*& getEdges() const override;

	unsigned int& getVertexColorBuffer() const override;

	unsigned int*& getTrianglesBuffers() const override;

	unsigned int& getEdgesBuffer() const override;

	unsigned int& getEdgeColorsBuffer() const override;

	unsigned int& getFacesVAO() const override;

	unsigned int& getEdgesVAO() const override;

	bool& getBuffered() const override;
};