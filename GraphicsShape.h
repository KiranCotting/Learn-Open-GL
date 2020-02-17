#pragma once
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include "Matrix.h"
#include "Vector.h"
#include "WebGLUtility.h"

/// <summary> A high level graphics object for representing any arbitrary polygon.
/// Intended to be inherited to create more specific geometries. </summary>
class GraphicsShape {
	//static unsigned short numVertices, numTriangleVertices, numEdgeVertices;
	//static float *vertices, *colors, *edgeColors;
	//static unsigned short *triangles, *edges;
	//static unsigned int vertexColorBuffer, trianglesBuffer, edgesBuffer, edgeColorsBuffer, program, facesVAO, edgesVAO;
	//static bool buffered, programLoaded;
public:
	/// <summary> The x position of this shape. Can be modified directly. </summary>
	float x;
	/// <summary> The y position of this shape. Can be modified directly. </summary>
	float y;
	/// <summary> The z position of this shape. Can be modified directly. </summary>
	float z;
	/// <summary> The x scale factor of this shape. Can be modified directly. </summary>
	float sx;
	/// <summary> The y scale factor of this shape. Can be modified directly. </summary>
	float sy;
	/// <summary> The z scale factor of this shape. Can be modified directly. </summary>
	float sz;
	/// <summary> The x-axis rotation of this shape, in degrees. Can be modified directly. </summary>
	float rx;
	/// <summary> The y-axis rotation of this shape, in degrees. Can be modified directly. </summary>
	float ry;
	/// <summary> The z-axis rotation of this shape, in degrees. Can be modified directly. </summary>
	float rz;
	/// <summary> Whether this shape should render in wireframe only. Can be modified directly. </summary>
	bool wire;
	/// <summary> Returns this shape's location as a vector. </summary>
	Vector getLocation() const;
	/// <summary> Set this shape's location. </summary>
	/// <param name="pos"> The new position of this shape. </param>
	void setLocation(const Vector& pos);
	/// <summary> Set this shape's location. </summary>
	/// <param name="x"> The new x position of this shape. </param>
	/// <param name="y"> The new position of this shape. </param>
	/// <param name="z"> The new position of this shape. </param>
	void setLocation(const float& x, const float& y, const float& z);
	/// <summary> Returns this shape's scale factors as a vector. </summary>
	Vector getScale() const;
	/// <summary> Set this shape's scale factors. </summary>
	/// <param name="scale"> The new scaling of this shape. </param>
	void setScale(const Vector& scale);
	/// <summary> Set this shape's scale factors. </summary>
	/// <param name="xscale"> The new x scaling of this shape. </param>
	/// <param name="yscale"> The new y scaling of this shape. </param>
	/// <param name="zscale"> The new z scaling of this shape. </param>
	void setScale(const float& xscale, const float& yscale, const float& zscale);
	/// <summary> Returns this shape's rotation as a vector. </summary>
	Vector getRotation() const;
	/// <summary> Set this shape's rotation. </summary>
	/// <param name="rotation"> The new rotation of this shape. </param>
	void setRotation(const Vector& rotation);
	/// <summary> Set this shape's rotation. </summary>
	/// <param name="xrotation"> The new x rotation of this shape. </param>
	/// <param name="yrotation"> The new y rotation of this shape. </param>
	/// <param name="zrotation"> The new z rotation of this shape. </param>
	void setRotation(const float& xrotation, const float& yrotation, const float& zrotation);
	/// <summary> Returns this shape's model matrix. This function computes a new matrix every time it is called. </summary>
	Matrix getModel() const;
	/// <summary> Buffers this shape's model data, as well as sets up the VAO for this shape. </summary>
	virtual void buffer();
	/// <summary> Renders this shape's edges, either for highlighting or wireframe purposes. </summary>
	virtual void drawEdges();
	/// <summary> Renders this shape's triangles. This is the main geometry of the shape. </summary>
	virtual void drawTriangles();
	/// <summary> The main render loop of this shape. Responsible for loading and setting up the relevant shaders,
	/// binding and buffering data, and calling buffer(), drawEdges(), and drawTriangles(). </summary>
	virtual void render(const Matrix&, const Matrix&);

protected:
	char currentLOD = 0;

	// The following block of getters exists so that each child of the GraphicsShape class may have separate static
	// versions of these variables, without sharing those static variables with the parent or each other, but while still
	// allowing GraphicsShape to provide inherited functions which use these variables.
	
	virtual char& getMaxLOD() const = 0;

	virtual unsigned short& getNumVertices() const = 0;

	virtual unsigned short*& getNumTriangleVertices() const = 0;

	virtual unsigned short& getNumEdgeVertices() const = 0;

	virtual float*& getVertices() const = 0;

	virtual float*& getColors() const = 0;

	virtual float*& getEdgeColors() const = 0;
	
	virtual unsigned short**& getTriangles() const = 0;

	virtual unsigned short*& getEdges() const = 0;

	virtual unsigned int& getVertexColorBuffer() const = 0;

	virtual unsigned int*& getTrianglesBuffers() const = 0;

	virtual unsigned int& getEdgesBuffer() const = 0;

	virtual unsigned int& getEdgeColorsBuffer() const = 0;

	virtual unsigned int& getFacesVAO() const = 0;

	virtual unsigned int& getEdgesVAO() const = 0;

	virtual bool& getBuffered() const = 0;

	// Constructor is protected to prevent instantiation.
	/// <summary> Shape constructor. </summary>
	GraphicsShape();

private:
	static unsigned int program;
	static bool programLoaded;
};
