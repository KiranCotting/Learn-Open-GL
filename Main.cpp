/*
Date: 12/5/19
Author: Kiran Cotting
Purpose: Learning OpenGL.
Creating using the tutorial at https://learnopengl.com/
*/
#define _USE_MATH_DEFINES
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <windows.h>
#include <thread>
#include <iostream>
using std::cout; using std::endl;
#include "Cube.h"
#include "Camera.h"

static const double frameTime = 1.0 / 60;

GLFWwindow* window;

Camera camera;

Vector cameraPosition = Vector(0, 0, 30);

Vector look = Vector(0, 0, -1);

int windowWidth = 1000;

int windowHeight = 1000;

float aspect = (float) windowWidth / (float) windowHeight;

float cameraTheta = M_PI / 2;

float cameraPhi = 0;

double prevMouseX, prevMouseY;

Cube cube1(5, 0, 0, 5, 5, 5);
Cube cube2(-5, 0, 0, 5, 5, 5);

int frameCount = 0;

// A callback to handle re-sizing of the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Handle mouse movement
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

// A function to contain all input related code
void processInput(GLFWwindow* window);

// Called once before rendering starts
void setup();

// Main render loop
void render(float);

int main() {
	glfwInit();

	// These two lines tell GLFW that the open GL version is 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Excludes backward compatibility and other extra stuff
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window object, used often
	window = glfwCreateWindow(windowWidth, windowHeight, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Keeps cursor locked to window
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set callback for mouse input
	glfwSetCursorPosCallback(window, cursor_position_callback);

	// If system can support raw mouse input, use it, as it is better for camera purposes
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	// Load Open GL functions using GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	setup();

	// Setup window re-size callback
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	LARGE_INTEGER prevTime, time;
	QueryPerformanceCounter(&prevTime);

	// Main render loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		// Determine time of frame
		QueryPerformanceCounter(&time);
		LARGE_INTEGER timerFreq;
		QueryPerformanceFrequency(&timerFreq);
		const double freq = 1.0f / timerFreq.QuadPart;
		const double timeSeconds = (time.QuadPart - prevTime.QuadPart) * freq;
		render((float) timeSeconds);
		glfwSwapBuffers(window);
		glfwPollEvents();
		if (timeSeconds < frameTime) {
			std::this_thread::sleep_for(std::chrono::milliseconds((int) ((frameTime - timeSeconds) * 1000)));
			if (frameCount % 60 == 59) {
				cout << "60 fps" << endl;
			}
		}
		else {
			if (frameCount % 60 == 59) {
				cout << 1.0 / timeSeconds << " fps" << endl;
			}
		}

		prevTime = time;
		++frameCount;
	}
	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) { 
	cameraTheta += (float) (xpos - prevMouseX) / 1000 * M_PI;
	cameraPhi += (float) (ypos - prevMouseY) / 1000 * M_PI;
	if (cameraPhi > M_PI / 2 - 0.0001f) {
		cameraPhi = M_PI / 2 - 0.0001f;
	} else if (cameraPhi < -M_PI / 2 + 0.0001f) {
		cameraPhi = -M_PI / 2 + 0.0001f;
	}
	prevMouseX = xpos;
	prevMouseY = ypos;
}

void processInput(GLFWwindow* window)
{
	Vector movement = Vector(0, 0, 0);
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movement += ~Vector(look.getX(), 0, look.getZ());
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movement -= ~Vector(look.getX(), 0, look.getZ());
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movement += ~(Vector(0, 1, 0) % look);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movement -= ~(Vector(0, 1, 0) % look);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		movement += Vector(0, 1, 0);
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		movement -= Vector(0, 1, 0);
	cameraPosition += movement;
}

void setup() {
	glfwGetCursorPos(window, &prevMouseX, &prevMouseY);

	// Camera
	camera.frustum(-5 * aspect, 5 * aspect, -5, 5, 10, 250);

	// Create a GL window
	glViewport(0, 0, 1000, 1000);
	// Create background color
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Turn on depth testing
	glClearDepth(1);
	glEnable(GL_DEPTH_TEST);
	// Back face culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void render(float time) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	look = -Vector(
		cosf(cameraPhi) * cosf(cameraTheta),
		sinf(cameraPhi),
		cosf(cameraPhi) * sinf(cameraTheta)
	);

	camera.viewPoint(cameraPosition, look, Vector(0, 1, 0));
	cube1.render(camera.getProjection(), camera.getView());
	cube2.render(camera.getProjection(), camera.getView());
}