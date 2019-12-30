#include "GraphicsShape.h"

GraphicsShape::GraphicsShape() {
	numVertices = 0;
	numTriangleVertices = 0;
	numEdgeVertices = 0;
	vertices = new float[0];
	colors = new float[0];
	edgeColors = new float[0];
	triangles = new unsigned short[0];
	edges = new unsigned short[0];
	wire = false;
	buffered = false;
	programLoaded = false;
	edgeColorsBuffer = 0;
	edgesBuffer = 0;
	trianglesBuffer = 0;
	vertexColorBuffer = 0;
	program = 0;
	facesVAO = 0;
	edgesVAO = 0;
	x = 0;
	y = 0;
	z = 0;
	sx = 1;
	sy = 1;
	sz = 1;
	rx = 0;
	ry = 0;
	rz = 0;
}

Vector GraphicsShape::getLocation() const {
	return Vector(x, y, z);
}

void GraphicsShape::setLocation(const Vector& pos) {
	x = pos.getX();
	y = pos.getY();
	z = pos.getZ();
}

void GraphicsShape::setLocation(const float& x, const float& y, const float& z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector GraphicsShape::getScale() const {
	return Vector(sx, sy, sz);
}

void GraphicsShape::setScale(const Vector& scale) {
	sx = scale.getX();
	sy = scale.getY();
	sz = scale.getZ();
}

void GraphicsShape::setScale(const float& sx, const float& sy, const float& sz) {
	this->sx = sx;
	this->sy = sy;
	this->sz = sz;
}

Vector GraphicsShape::getRotation() const {
	return Vector(rx, ry, rz);
}

void GraphicsShape::setRotation(const Vector& rotation) {
	rx = rotation.getX();
	ry = rotation.getY();
	rz = rotation.getZ();
}

void GraphicsShape::setRotation(const float& rx, const float& ry, const float& rz) {
	this->rx = rx;
	this->ry = ry;
	this->rz = rz;
}

Matrix GraphicsShape::getModel() const {
	Matrix model = Matrix::identity().scale(sx, sy, sz).rotate(rx, ry, rz).translate(x, y, z);
	return model;
}

void GraphicsShape::buffer() {
	float* verticesColor = new float[numVertices * 7];
	for (int i = 0; i < numVertices; ++i) {
		verticesColor[i * 7] = vertices[i * 3];
		verticesColor[i * 7 + 1] = vertices[i * 3 + 1];
		verticesColor[i * 7 + 2] = vertices[i * 3 + 2];
		verticesColor[i * 7 + 3] = colors[i * 4];
		verticesColor[i * 7 + 4] = colors[i * 4 + 1];
		verticesColor[i * 7 + 5] = colors[i * 4 + 2];
		verticesColor[i * 7 + 6] = colors[i * 4 + 3];
	}

	glGenBuffers(1, &vertexColorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexColorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVertices * 7, verticesColor, GL_STATIC_DRAW);

	glGenBuffers(1, &trianglesBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, trianglesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * numTriangleVertices, triangles, GL_STATIC_DRAW);

	glGenBuffers(1, &edgesBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * numEdgeVertices, edges, GL_STATIC_DRAW);

	glGenBuffers(1, &edgeColorsBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, edgeColorsBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numEdgeVertices * 4, edgeColors, GL_STATIC_DRAW);

	// Set up shader attributes
	unsigned int attribShapeLocation = glGetAttribLocation(program, "shapeLocation");
	unsigned int attribShapeColor = glGetAttribLocation(program, "shapeColor");

	// Set up for drawing faces
	glGenVertexArrays(1, &facesVAO);
	glBindVertexArray(facesVAO);

	glBindBuffer(GL_ARRAY_BUFFER, vertexColorBuffer);

	// positions
	glVertexAttribPointer(attribShapeLocation, 3, GL_FLOAT, false, 28, (void*)0);
	glVertexAttribPointer(attribShapeColor, 4, GL_FLOAT, false, 28, (void*)12);

	// colors
	glEnableVertexAttribArray(attribShapeLocation);
	glEnableVertexAttribArray(attribShapeColor);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, trianglesBuffer);

	glBindVertexArray(0);

	// Set up for drawing edges
	glGenVertexArrays(1, &edgesVAO);
	glBindVertexArray(edgesVAO);

	// positions
	glBindBuffer(GL_ARRAY_BUFFER, vertexColorBuffer);
	glVertexAttribPointer(attribShapeLocation, 3, GL_FLOAT, false, 28, (void*)0);
	glEnableVertexAttribArray(attribShapeLocation);

	// colors
	glBindBuffer(GL_ARRAY_BUFFER, edgeColorsBuffer);
	glVertexAttribPointer(attribShapeColor, 4, GL_FLOAT, false, 0, (void*)0);
	glEnableVertexAttribArray(attribShapeColor);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgesBuffer);

	glBindVertexArray(0);

	buffered = true;

	delete[] verticesColor;
}

void GraphicsShape::drawEdges() {
	glDrawElements(GL_LINES, numEdgeVertices, GL_UNSIGNED_SHORT, (void*)0);
}

void GraphicsShape::drawTriangles() {
	glDrawElements(GL_TRIANGLE_STRIP, numTriangleVertices, GL_UNSIGNED_SHORT, (void*)0);
}

void GraphicsShape::render(const Matrix& projection, const Matrix& view) {
	// Set up program
	if (!programLoaded) {
		program = createProgram("vertex.txt", "fragment.txt");
		programLoaded = true;
	}

	// Set up buffers
	if (!buffered) {
		buffer();
	}

	glUseProgram(program);

	unsigned int modelUniform = glGetUniformLocation(program, "model");
	unsigned int projectionUniform = glGetUniformLocation(program, "projection");
	unsigned int viewUniform = glGetUniformLocation(program, "view");
	glUniformMatrix4fv(modelUniform, 1, true, getModel().getValues());
	glUniformMatrix4fv(projectionUniform, 1, true, projection.getValues());
	glUniformMatrix4fv(viewUniform, 1, true, view.getValues());

	// Bind everything for drawing faces
	glBindVertexArray(facesVAO);

	// Draw from triangles array
	if (!wire) {
		drawTriangles();
	}

	// Bind everything for drawing edges
	glBindVertexArray(edgesVAO);

	// Draw from edges array
	drawEdges();

	glBindVertexArray(0);

	glUseProgram(0);
}

GraphicsShape::~GraphicsShape() {
	delete[] vertices;
	delete[] colors;
	delete[] edgeColors;
	delete[] triangles;
	delete[] edges;
	glDeleteProgram(program);
}