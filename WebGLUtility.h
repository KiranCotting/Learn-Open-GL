#pragma once
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <windows.h>
#include <gl/glu.h>
#include <string>
using std::string;
#include <iostream>
using std::cout; using std::endl;
#include <fstream>
using std::ifstream;

/// <summary> Loads a shader from a file and returns it as a string. </summary>
/// <param name="path"> The relative path to the shader file. </param>
string getShader(string path);

/// <summary> Creates a WebGL program from a vertex and a fragment shader. </summary>
/// <param name="vertex"> The relative path to the vertex shader file. </param>
/// <param name="fragment"> The relative path to the fragment shader file. </param>
unsigned int createProgram(string vertex, string fragment);

void CheckOpenGLError(const char* stmt, const char* fname, int line);

#ifdef _DEBUG
	#define GL_CHECK(stmt) do { \
        stmt; \
        CheckOpenGLError(#stmt, __FILE__, __LINE__); \
    } while (0)

	#define GL_CHECK_E() do { \
        CheckOpenGLError("EMPTY", __FILE__, __LINE__); \
    } while (0)
#else
	#define GL_CHECK(stmt) stmt
	#define GL_CHECK_E() void
#endif
