#include "GraphicsShape.h"

unsigned int GraphicsShape::program;
bool GraphicsShape::programLoaded;

GraphicsShape::GraphicsShape() {
	x = 0;
	y = 0;
	z = 0;
	sx = 1;
	sy = 1;
	sz = 1;
	rx = 0;
	ry = 0;
	rz = 0;
	wire = false;
	programLoaded = false;
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
	Matrix model = Matrix::identity().scale(sx, sy, sz).rotate(rx, ry, rz, true).translate(x, y, z);
	return model;
}

void GraphicsShape::buffer() {
	float* verticesColor = new float[getNumVertices() * 7];
	for (int i = 0; i < getNumVertices(); ++i) {
		verticesColor[i * 7] = getVertices()[i * 3];
		verticesColor[i * 7 + 1] = getVertices()[i * 3 + 1];
		verticesColor[i * 7 + 2] = getVertices()[i * 3 + 2];
		verticesColor[i * 7 + 3] = getColors()[i * 4];
		verticesColor[i * 7 + 4] = getColors()[i * 4 + 1];
		verticesColor[i * 7 + 5] = getColors()[i * 4 + 2];
		verticesColor[i * 7 + 6] = getColors()[i * 4 + 3];
	}

	glGenBuffers(1, &getVertexColorBuffer());
	glBindBuffer(GL_ARRAY_BUFFER, getVertexColorBuffer());
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * getNumVertices() * 7, verticesColor, GL_STATIC_DRAW);

	for (int i = 0; i <= getMaxLOD(); ++i) {
		glGenBuffers(1, &getTrianglesBuffers()[i]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, getTrianglesBuffers()[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * getNumTriangleVertices()[i], getTriangles()[i], GL_STATIC_DRAW);
	}

	glGenBuffers(1, &getEdgesBuffer());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, getEdgesBuffer());
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * getNumEdgeVertices(), getEdges(), GL_STATIC_DRAW);

	glGenBuffers(1, &getEdgeColorsBuffer());
	glBindBuffer(GL_ARRAY_BUFFER, getEdgeColorsBuffer());
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * getNumEdgeVertices() * 4, getEdgeColors(), GL_STATIC_DRAW);

	// Set up shader attributes
	unsigned int attribShapeLocation = glGetAttribLocation(program, "shapeLocation");
	unsigned int attribShapeColor = glGetAttribLocation(program, "shapeColor");

	// Set up for drawing faces
	glGenVertexArrays(1, &getFacesVAO());
	glBindVertexArray(getFacesVAO());

	glBindBuffer(GL_ARRAY_BUFFER, getVertexColorBuffer());

	// positions
	glVertexAttribPointer(attribShapeLocation, 3, GL_FLOAT, false, 28, (void*)0);
	glVertexAttribPointer(attribShapeColor, 4, GL_FLOAT, false, 28, (void*)12);

	// colors
	glEnableVertexAttribArray(attribShapeLocation);
	glEnableVertexAttribArray(attribShapeColor);

	glBindVertexArray(0);

	// Set up for drawing edges
	glGenVertexArrays(1, &getEdgesVAO());
	glBindVertexArray(getEdgesVAO());

	// positions
	glBindBuffer(GL_ARRAY_BUFFER, getVertexColorBuffer());
	glVertexAttribPointer(attribShapeLocation, 3, GL_FLOAT, false, 28, (void*)0);
	glEnableVertexAttribArray(attribShapeLocation);

	// colors
	glBindBuffer(GL_ARRAY_BUFFER, getEdgeColorsBuffer());
	glVertexAttribPointer(attribShapeColor, 4, GL_FLOAT, false, 0, (void*)0);
	glEnableVertexAttribArray(attribShapeColor);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, getEdgesBuffer());

	glBindVertexArray(0);

	getBuffered() = true;

	delete[] verticesColor;
}

void GraphicsShape::drawEdges() {
	glDrawElements(GL_LINES, getNumEdgeVertices(), GL_UNSIGNED_SHORT, (void*)0);
}

void GraphicsShape::drawTriangles() {
	glDrawElements(GL_TRIANGLE_STRIP, getNumTriangleVertices()[currentLOD], GL_UNSIGNED_SHORT, (void*)0);
}

void GraphicsShape::render(const Matrix& projection, const Matrix& view) {
	// Set up program
	if (!programLoaded) {
		program = createProgram("vertex.txt", "fragment.txt");
		programLoaded = true;
	}

	// Set up buffers
	if (!getBuffered()) {
		buffer();
	}

	// Determine Level of Detail
	if (getMaxLOD() > 0) {
		Vector position(x, y, z);
		position = view * position;
		currentLOD = (char)-100 / position.getZ();
		if (currentLOD > getMaxLOD()) {
			currentLOD = getMaxLOD();
		}
		else if (currentLOD < 0) {
			currentLOD = 0;
		}
	}

	glUseProgram(program);

	unsigned int modelUniform = glGetUniformLocation(program, "model");
	unsigned int projectionUniform = glGetUniformLocation(program, "projection");
	unsigned int viewUniform = glGetUniformLocation(program, "view");
	glUniformMatrix4fv(modelUniform, 1, true, getModel().getValues());
	glUniformMatrix4fv(projectionUniform, 1, true, projection.getValues());
	glUniformMatrix4fv(viewUniform, 1, true, view.getValues());

	// Bind everything for drawing faces, except the triangles element array
	glBindVertexArray(getFacesVAO());

	// Bind the correct element array based on LOD
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, getTrianglesBuffers()[currentLOD]);

	// Draw from triangles array
	if (!wire) {
		drawTriangles();
	}

	// Bind everything for drawing edges
	glBindVertexArray(getEdgesVAO());

	// Draw from edges array
	drawEdges();

	glBindVertexArray(0);

	glUseProgram(0);
}