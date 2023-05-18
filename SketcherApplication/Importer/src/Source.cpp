#include <iostream>
#include <sstream>
#include <string>

#define GLFW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Camera.h"
#include "Mesh.h"


const char* APP_TITLE = "Introduction to Modern OpenGL";
int gWindowWidth = 1024;
int gWindowHeight = 768;
GLFWwindow* gWindow = NULL;
bool gWireframe = false;

FPSCamera fpsCamera(glm::vec3(0.0f, 3.0f, 10.0f));
const double ZOOM_SENSITYVITY = -3.0;
const float MOVE_SPEED = 5.0;
const float MOUSE_SENSITIVITY = 0.1f;

void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode);
void glfw_OnFrameBufferSize(GLFWwindow* window, int height, int width);
void glfw_onMouseMove(GLFWwindow* window, double posX, double posY);
void glfw_onMouseScroll(GLFWwindow* window, double deltaX, double deltaY);
void update(double elapsedTime);
void showFPS(GLFWwindow* window);
bool initOpenGL();

int main() {

	if (!initOpenGL()) {
		std::cerr << "GLFW initilization failed" << std::endl;
		return EXIT_FAILURE;
	}

	ShaderProgram lightShader;
	lightShader.loadShaders("shaders/basic.vert", "shaders/basic.frag");

	ShaderProgram lightingShader;
	lightingShader.loadShaders("shaders/lighting.vert", "shaders/lighting.frag");

	// Model Positions
	glm::vec3 modelPos[] = {
		glm::vec3(-3.5f, 0.0f, 0.0f),	// crate1
		glm::vec3(3.5f, 0.0f, 0.0f),	// crate2
		glm::vec3(0.0f, 0.0f, -2.0f),	// robot
		glm::vec3(0.0f, 0.0f, 0.0f),	// floor
		glm::vec3(0.0f, 0.0f, 2.0f),	// pin
		glm::vec3(-2.0f, 0.0f, 2.0f)	// bunny
	};

	// Model scale
	glm::vec3 modelScale[] = {
		glm::vec3(1.0f, 1.0f, 1.0f),	// crate1
		glm::vec3(1.0f, 1.0f, 1.0f),	// crate2
		glm::vec3(1.0f, 1.0f, 1.0f),	// robot
		glm::vec3(10.0f, 1.0f, 10.0f),	// floor
		glm::vec3(0.1f, 0.1f, 0.1f),	// pin
		glm::vec3(0.7f, 0.7f, 0.7f)		// bunny
	};

	//Load meshes and textures
	const int numModels = 6;
	Mesh mesh[numModels];
	Texture2D texture[numModels];

	mesh[0].loadOBJ("models/crate.obj");
	mesh[1].loadOBJ("models/woodcrate.obj");
	mesh[2].loadOBJ("models/robot.obj");
	mesh[3].loadOBJ("models/floor.obj");
	mesh[4].loadOBJ("models/bowling_pin.obj");
	mesh[5].loadOBJ("models/bunny.obj");

	texture[0].loadTexture("textures/crate.jpg", true);
	texture[1].loadTexture("textures/woodcrate_diffuse.jpg", true);
	texture[2].loadTexture("textures/robot_diffuse.jpg", true);
	texture[3].loadTexture("textures/tile_floor.jpg", true);
	texture[4].loadTexture("textures/AMF.tga", true);
	texture[5].loadTexture("textures/bunny_diffuse.jpg", true);

	Mesh lightMesh;
	lightMesh.loadOBJ("light.obj");

	double lastTime = glfwGetTime();
	float angle = 0.0f;

	while (!glfwWindowShouldClose(gWindow)) {
		showFPS(gWindow);

		double currentTime = glfwGetTime();
		double deltaTime = currentTime - lastTime;


		glfwPollEvents();
		update(deltaTime);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 model(1.0), view(1.0), projection(1.0);


		view = fpsCamera.getViewMatrix();
		projection = glm::perspective(glm::radians(fpsCamera.getFOV()), (float)gWindowWidth / (float)gWindowHeight, 0.1f, 100.0f);

		// light position
		glm::vec3 lightPos(0.0f, 1.0f, 10.0f);
		glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

		// move light
		angle += (float)deltaTime * 50.0f;
		lightPos.x = 8.0f * sinf(glm::radians(angle));

		lightingShader.use();

		lightingShader.setUniform("view", view);
		lightingShader.setUniform("projection", projection);

		for (int i = 0; i < numModels; i++) {
			model = glm::translate(glm::mat4(1.0), modelPos[i]) * glm::scale(glm::mat4(1.0), modelScale[i]);
			lightingShader.setUniform("model", model);
			texture[i].bind(0);
			mesh[i].draw();
			texture[i].unbind(0);
		}

		// render the light
		model = glm::translate(glm::mat4(1.0), lightPos);
		lightShader.use();
		lightShader.setUniform("lightColor", lightColor);
		lightShader.setUniform("model", model);
		lightShader.setUniform("view", view);
		lightShader.setUniform("projection", projection);
		lightMesh.draw();

		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);

		glfwSwapBuffers(gWindow);
		lastTime = currentTime;
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}


void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	//if (key == GLFW_KEY_W && action == GLFW_PRESS) {
	//	gWireframe = !gWireframe;
	//	if (gWireframe)
	//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//	else
	//		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//}
}

void glfw_OnFrameBufferSize(GLFWwindow* window, int height, int width) {
	gWindowWidth = width;
	gWindowHeight = height;
	glViewport(0, 0, gWindowWidth, gWindowHeight);
}

void glfw_onMouseMove(GLFWwindow* window, double posX, double posY)
{
	/*static glm::vec2 lastMousePos = glm::vec2(0, 0);

	if (glfwGetMouseButton(gWindow, GLFW_MOUSE_BUTTON_LEFT) == 1) {
		gYaw -= ((float)posX - lastMousePos.x) * MOUSE_SENSITIVITY;
		gPitch += ((float)posY - lastMousePos.y) * MOUSE_SENSITIVITY;
	}

	if (glfwGetMouseButton(gWindow, GLFW_MOUSE_BUTTON_RIGHT) == 1) {
		float dx = 0.01f * ((float)posX - lastMousePos.x);
		float dy = 0.01f * ((float)posY - lastMousePos.y);
		gRadius += dx - dy;
	}
	lastMousePos.x = (float)posX;
	lastMousePos.y = (float)posY;*/
}

void glfw_onMouseScroll(GLFWwindow* window, double deltaX, double deltaY)
{
	double fov = fpsCamera.getFOV() + deltaY * ZOOM_SENSITYVITY;

	fov = glm::clamp(fov, 1.0, 120.0);

	fpsCamera.setFOV((float)fov);
}

void update(double elapsedTime)
{
	double mouseX, mouseY;

	glfwGetCursorPos(gWindow, &mouseX, &mouseY);

	fpsCamera.rotate((float)(gWindowWidth / 2.0 - mouseX) * MOUSE_SENSITIVITY, (float)(gWindowHeight / 2.0 - mouseY) * MOUSE_SENSITIVITY);

	glfwSetCursorPos(gWindow, gWindowWidth / 2.0, gWindowHeight / 2.0);

	// Forwad/Backward
	if (glfwGetKey(gWindow, GLFW_KEY_W) == GLFW_PRESS)
		fpsCamera.move(MOVE_SPEED * (float)elapsedTime * fpsCamera.getLook());
	else if (glfwGetKey(gWindow, GLFW_KEY_S) == GLFW_PRESS)
		fpsCamera.move(MOVE_SPEED * (float)elapsedTime * -fpsCamera.getLook());

	// Strafe left/right
	if (glfwGetKey(gWindow, GLFW_KEY_A) == GLFW_PRESS)
		fpsCamera.move(MOVE_SPEED * (float)elapsedTime * -fpsCamera.getRight());
	else if (glfwGetKey(gWindow, GLFW_KEY_D) == GLFW_PRESS)
		fpsCamera.move(MOVE_SPEED * (float)elapsedTime * fpsCamera.getRight());

	// Up/Down
	if (glfwGetKey(gWindow, GLFW_KEY_Z) == GLFW_PRESS)
		fpsCamera.move(MOVE_SPEED * (float)elapsedTime * fpsCamera.getUp());
	else if (glfwGetKey(gWindow, GLFW_KEY_X) == GLFW_PRESS)
		fpsCamera.move(MOVE_SPEED * (float)elapsedTime * -fpsCamera.getUp());
}

void showFPS(GLFWwindow* window) {
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

bool initOpenGL()
{
	if (!glfwInit()) {
		std::cerr << "GLFW initialization failed" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	// depricated functions not supported now
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);	// only for mac users (forward compatibility)

	gWindow = glfwCreateWindow(gWindowHeight, gWindowHeight, APP_TITLE, NULL, NULL);
	if (gWindow == NULL) {
		std::cerr << "FAILED to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(gWindow); // make the context of our window the main context on the current thread


	glfwSetKeyCallback(gWindow, glfw_onKey);
	//glfwSetFramebufferSizeCallback(gWindow, glfw_OnFrameBufferSize);
	glfwSetCursorPosCallback(gWindow, glfw_onMouseMove);
	glfwSetScrollCallback(gWindow, glfw_onMouseScroll);

	glfwSetInputMode(gWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(gWindow, gWindowWidth / 2.0, gWindowHeight / 2.0);


	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "GLEW initialization failed" << std::endl;
		return false;
	}
	glClearColor(0.23f, 0.38f, 0.47f, 1.0f);
	glViewport(0, 0, gWindowWidth, gWindowHeight);
	glEnable(GL_DEPTH_TEST);
	return true;

}
