#include "OpenGLWrapper.h"

GLFWwindow* OpenGLWrapper::gWindow = NULL;

OpenGLWrapper::OpenGLWrapper(std::vector<float> &vertices) {
	mVertices = vertices;
}


int OpenGLWrapper::OpenGLmain() {

	if (!initOpenGL()) {
		std::cerr << "GLFW initilization failed" << std::endl;
		return EXIT_FAILURE;
	}
		
	GLuint vbo, vao;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mVertices), &mVertices[0], GL_STATIC_DRAW);

	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(mVertices), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//color
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(mVertices), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	ShaderProgram shaderProgram;
	shaderProgram.loadShaders("shaders/basic.vert", "shaders/basic.frag");

	// Main loop
	while (!glfwWindowShouldClose(gWindow)) {
		showFPS(gWindow);
		glfwPollEvents();	// checks if any events are triggered

		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.use();

		glBindVertexArray(vao);

		glDrawArrays(GL_TRIANGLES, 0, mVertices.size());

		glBindVertexArray(0);
		glfwSwapBuffers(gWindow);
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glfwTerminate();
	return EXIT_SUCCESS;
}

void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void OpenGLWrapper::showFPS(GLFWwindow* window) {
	static double previousSeconds = 0.0;
	static int frameCount = 0;
	double elapsedSeconds;
	double currentSeconds = glfwGetTime();

	elapsedSeconds = currentSeconds - previousSeconds;

	// limit text update 4 times per second
	if (elapsedSeconds > 0.25) {
		previousSeconds = currentSeconds;
		double fps = (double)frameCount / elapsedSeconds;
		double msPerFrame = 1000.0 / fps;

		std::ostringstream outs;
		outs.precision(3);
		outs << std::fixed
			<< APP_TITLE << "  "
			<< "FPS: " << fps << "  "
			<< "Frame Time: " << msPerFrame << " (ms)";
		glfwSetWindowTitle(window, outs.str().c_str());

		frameCount = 0;
	}
	frameCount++;
}

bool OpenGLWrapper::initOpenGL()
{
	if (!glfwInit()) {
		std::cerr << "GLFW initialization failed" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	gWindow = glfwCreateWindow(gWindowHeight, gWindowHeight, APP_TITLE, NULL, NULL);
	if (gWindow == NULL) {
		std::cerr << "FAILED to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(gWindow); // make the context of our window the main context on the current thread

	glfwSetKeyCallback(gWindow, glfw_onKey);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "GLEW initialization failed" << std::endl;
		return false;
	}
	glClearColor(0.23f, 0.38f, 0.47f, 1.0f);
	return true;

}
