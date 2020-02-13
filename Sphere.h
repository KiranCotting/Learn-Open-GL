#pragma once
#include "GraphicsShape.h"
#include <map>
#include <vector>

const char MAX_SPHERE_LOD = 5;

/// <summary> A child of GraphicsShape, to represent any Cube. </summary>
class Sphere : public GraphicsShape {
public:
	/// <summary> Cube constructor. </summary>
	/// <param name="levelOfDetail"> The level of detail to use when creating this sphere. Higher is better detail, but less efficient. </param>
	/// <param name="x"> The x-coord of this sphere. </param>
	/// <param name="y"> The y-coord of this sphere. </param>
	/// <param name="z"> The z-coord of this sphere. </param>
	/// <param name="sx"> The x-scale of this sphere. </param>
	/// <param name="sy"> The y-scale of this sphere. </param>
	/// <param name="sz"> The z-scale of this sphere. </param>
	/// <param name="rx"> The x-rotation of this sphere, in degrees. </param>
	/// <param name="ry"> The y-rotation of this sphere, in degrees. </param>
	/// <param name="rz"> The z-rotation of this sphere, in degrees. </param>
	Sphere(const int& levelOfDetail = 1, const float& x = 0, const float& y = 0, const float& z = 0, const float& sx = 0, const float& sy = 0, const float& sz = 0, const float& rx = 0, const float& ry = 0, const float& rz = 0);
	
	void drawTriangles() override;

	void render(const Matrix&, const Matrix&) override;

private:
	struct Triangle {
		unsigned short a, b, c;
		Triangle(unsigned short a, unsigned short b, unsigned short c) : a(a), b(b), c(c) {}
	};

	char levelOfDetail;
	static unsigned short numVertices, numTriangleVertices, numEdgeVertices;
	static float* vertices, * colors, * edgeColors;
	static unsigned short* triangles, * edges;
	static unsigned int vertexColorBuffer, trianglesBuffer, edgesBuffer, edgeColorsBuffer, facesVAO, edgesVAO;
	static bool buffered, initialized;

	void createPoints(std::vector<Triangle>&, std::vector<Vector>&, std::map<unsigned int, unsigned short>&, const char&);

	unsigned short getMidPoint(unsigned short a, unsigned short b, std::vector<Vector>&, std::map<unsigned int, unsigned short>&);

	unsigned short& getNumVertices() const override;

	unsigned short& getNumTriangleVertices() const override;

	unsigned short& getNumEdgeVertices() const override;

	float*& getVertices() const override;

	float*& getColors() const override;

	float*& getEdgeColors() const override;

	unsigned short*& getTriangles() const override;

	unsigned short*& getEdges() const override;

	unsigned int& getVertexColorBuffer() const override;

	unsigned int& getTrianglesBuffer() const override;

	unsigned int& getEdgesBuffer() const override;

	unsigned int& getEdgeColorsBuffer() const override;

	unsigned int& getFacesVAO() const override;

	unsigned int& getEdgesVAO() const override;

	bool& getBuffered() const override;
};