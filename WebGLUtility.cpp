#include "WebGLUtility.h"

string getShader(string path) {
	ifstream file;
	file.open(path);
	if (file.is_open()) {
		string shader = "";
		string line = "";
		while (!file.eof()) {
			getline(file, line);
			shader += line + '\n';
		}
		file.close();
		return shader;
	}
	else {
		cout << "Unable to open shader file at path: " << path << endl;
		throw new std::runtime_error("Unable to open shader.");
	}
}

unsigned int createProgram(string vertex, string fragment) {
	// Create program and shader objects
	unsigned int program = glCreateProgram();
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Retrieve vertex and fragment source strings
	string vertexSourceString = getShader(vertex);
	string fragmentSourceString = getShader(fragment);
	// Convert strings to c-style
	const char* vertexSourceCString = vertexSourceString.c_str();
	const char* fragmentSourceCString = fragmentSourceString.c_str();
	// Add the source strings to the shader objects
	glShaderSource(vertexShader, 1, &vertexSourceCString, 0);
	glShaderSource(fragmentShader, 1, &fragmentSourceCString, 0);
	// Compile the shaders
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);
	int isCompiled = false;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (!isCompiled) {
		int maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		char* infoLog = new char[maxLength];
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
		cout << "Vertex shader failed to compile:" << endl;
		cout << infoLog;
		delete[] infoLog;
		throw new std::runtime_error("Vertex shader failed to compile.");
	}
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (!isCompiled) {
		int maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		char* infoLog = new char[maxLength];
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
		cout << "Fragment shader failed to compile:" << endl;
		cout << infoLog;
		delete[] infoLog;
		throw new std::runtime_error("Fragment shader failed to compile.");
	}
	// Attach shaders to the program
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	// Link shaders together
	glLinkProgram(program);
	int isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		int maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		char* infoLog = new char[maxLength];
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(program);
		// Don't leak shaders either.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// Use the infoLog
		cout << "Could not link program." << endl;
		cout << infoLog;

		throw new std::runtime_error("Could not link program.");
	}
	// Remove shader objects from program (Shaders are not removed, just the objects used to load them)
	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);
	// Delete these objects to avoid leaking anything
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return program;
}

void CheckOpenGLError(const char* stmt, const char* fname, int line)
{
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
	{
		printf("OpenGL error %08x, at %s:%i - for %s\n", err, fname, line, stmt);
		printf((const char*) gluErrorString(err));
		abort();
	}
}
