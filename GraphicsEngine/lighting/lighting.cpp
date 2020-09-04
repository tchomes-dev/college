#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Shader/Shader.h>
#include <Camera/Camera.h>
#include <Model/Model.h>
#include <Light/Light.h>

#include <iostream>

using namespace std;

//settings
//---------------------
const unsigned int width = 800;
const unsigned int height = 600;

//camera setup
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool firstMouse = true;
float lastX = width / 2;
float lastY = height / 2;

//timing
float deltaTime = 0.0f, lastFrame = 0.0f;
//flashlight settings
bool lightToggle = false;
glm::vec3 flashlightColor = glm::vec3(0.0f);

//method initialization
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

int main() {

	//glfw: initialize and configure
	//-----------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//glfw window creation
	//-----------------------------------
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL: Lighting", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW Window" << std::endl; glfwTerminate();
		return -1;
	}

	//set callbacks
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//tell glfw to capture mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//glad: load all OpenGL function pointers
	//-----------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	stbi_set_flip_vertically_on_load(true);
	
	//build and compile our shader program
	//-----------------------------------
	Shader ourShader("C:/Users/Tony/Dropbox/Model_Data/backpack/backpack.vs", "C:/Users/Tony/Dropbox/Model_Data/backpack/backpack.fs");
	Shader lampShader("C:/Users/Tony/Dropbox/Model_Data/lamp/lampShader.vs", "C:/Users/Tony/Dropbox/Model_Data/lamp/lampShader.fs");

	//load model (replace with path to obj file)
	Model backpack("C:/Users/Tony/Dropbox/Model_Data/sponza/sponza.obj");
	Model lamp("C:/Users/Tony/Dropbox/Model_Data/lamp/lamp.obj");

	//Light setup
	Light light(ourShader, camera);

	//set up vertex data (and buffer(s)) and configure vertex attributes
	//-----------------------------------
	glm::vec3 pointLightColors[] = {
		glm::vec3(1.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
	};

	//render loop
	while (!glfwWindowShouldClose(window)) {
		glm::vec3 pointLightPositions[] = {
		glm::vec3(sin(glfwGetTime()) * 4.0f,  0.0f,  4.0f + -cos(glfwGetTime()) / 4.0f),
		glm::vec3(2.3f, 3.3f -sin(glfwGetTime()) * 4.0f, -4.0f + cos(glfwGetTime()) * 4.0f),
		glm::vec3(-4.0f + sin(glfwGetTime()) * 4.0f,  2.0f, -5.0f + -cos(glfwGetTime()) * 4.0f),
		glm::vec3(5.0f - sin(glfwGetTime()) * 4.0f,  0.0f, -3.0f + cos(glfwGetTime()) * 4.0f)
		};

		//per-frame time logic
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//input
		processInput(window);

		//rendering commands
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ourShader.use();

		//define model, camera and projection matrices
		//-----------------------------------
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.1f, 100.0f);
		ourShader.setMat4("view", view);
		ourShader.setMat4("projection", projection);

		//model translation and scaling			
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.02f));
		//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		ourShader.setMat4("model", model);

		//lighting
		for (int i = 0; i < 4; i++) {
			light.setPointLight(pointLightColors[i], pointLightPositions[i], glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09, 0.032, i);
		}
		backpack.Draw(ourShader);

		//lamp postitional translation and scaling
		lampShader.use();
		lampShader.setMat4("view", view);
		lampShader.setMat4("projection", projection);
		for (int i = 0; i < 4; i++) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, glm::vec3(0.4f));
			lampShader.setMat4("model", model);
			lampShader.setVec3("color", pointLightColors[i]);
			lamp.Draw(lampShader);
		}
		//check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

//process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//------------------------------
void processInput(GLFWwindow* window) {
	//exit
	if (glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	//movement controls
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.ProcessKeyboard(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		camera.ProcessKeyboard(UP, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		camera.ProcessKeyboard(DOWN, deltaTime);
	}

	//flashlight toggle
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		if (lightToggle == false) {
			lightToggle = true;
			flashlightColor = glm::vec3(1.0f);
		} else {
			lightToggle = false;
			flashlightColor = glm::vec3(0.0f);
		}
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll(yoffset);
}

//glfw: whenever the window size changes this callback function executes
//-------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
