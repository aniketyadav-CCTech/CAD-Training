#ifndef OPENGLWRAPPER_H
#define OPENGLWRAPPER_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define GLFW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "ShaderProgram.h"
#include "Export.h"

void DllExport glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode);
class DllExport OpenGLWrapper
{
	const int gWindowWidth = 800;
	const int gWindowHeight = 600;
public:
	static GLFWwindow* gWindow;
	const char* APP_TITLE = "Introduction to Modern OpenGL";
	enum Attributes {
		AY_ATTRIBUTE_POSITION = 0,
		AY_ATTRIBUTE_COLOR,
		AY_ATTRIBUTE_TEXCOORD,
		AY_ATTRIBUTE_NORMAL
	};
	OpenGLWrapper(std::vector<float> &vertices);
	void showFPS(GLFWwindow* window);
	bool initOpenGL();
	int OpenGLmain();

	std::vector<float> mVertices;

};

#endif // !OPENGLWRAPPER_H