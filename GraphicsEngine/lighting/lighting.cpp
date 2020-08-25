#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Shader/Shader.h>
#include <Camera/Camera.h>
#include <Model/Model.h>

#include <iostream>

using namespace std;

//settings
//---------------------
const unsigned int width = 800;
const unsigned int height = 600;

//camera
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
void setDirectionalLight(Shader shader, glm::vec3 color, glm::vec3 direction, glm::vec3 specular);
void setPointLight(Shader shader, glm::vec3 color, glm::vec3 position, glm::vec3 specular, float attenuationConstant, float attenuationLinear, float attenuationQuadratic, int pointLightNumber);
void setSpotLight(Shader shader, glm::vec3 color, glm::vec3 specular, float attenuationConstant, float attenuationLinear, float attenuationQuadratic, float cutOff, float outerCutOff);

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
	Shader ourShader("object data/backpack/backpack.vs", "object data/backpack/backpack.fs");
	Shader lampShader("object data/lamp/lampShader.vs", "object data/lamp/lampShader.fs");

	//load model (replace with path to obj file)
	Model backpack("C:/Users/Tony/Documents/GitHub/box/GraphicsEngine/lighting/object data/backpack/backpack.obj");

	//set up vertex data (and buffer(s)) and configure vertex attributes
	//-----------------------------------

	//render loop
	while (!glfwWindowShouldClose(window)) {
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

		//lighting
		setPointLight(ourShader, glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(-3.0f, 5.0f, -7.0f), glm::vec3(1.0f), 1.0f, 0.09, 0.032, 1);

		//define model, camera and projection matrices
		//-----------------------------------
		ourShader.use();
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.1f, 100.0f);
		ourShader.setMat4("view", view);
		ourShader.setMat4("projection", projection);

		//send model matricies to shaders
		//container model translation and scaling			
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f));
		ourShader.setMat4("model", model);
		backpack.Draw(ourShader);

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

//sets directional light
void setDirectionalLight(Shader shader, glm::vec3 color, glm::vec3 direction, glm::vec3 specular) {
	glm::vec3 diffuseColor = color * glm::vec3(0.5f);
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);

	shader.setVec3("dirLight.direction", direction);
	shader.setVec3("dirLight.ambient", ambientColor);
	shader.setVec3("dirLight.diffuse", diffuseColor);
	shader.setVec3("dirLight.specular", specular);
}

//sets point light
void setPointLight(Shader shader, glm::vec3 color, glm::vec3 position, glm::vec3 specular, float attenuationConstant, float attenuationLinear, float attenuationQuadratic, int pointLightNumber) {
	string pointLightNum = to_string(pointLightNumber);
	glm::vec3 diffuseColor = color * glm::vec3(0.5f);
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);

	shader.setVec3("pointLights[" + pointLightNum + "].position", position);
	shader.setVec3("pointLights[" + pointLightNum + "].ambient", ambientColor);
	shader.setVec3("pointLights[" + pointLightNum + "].diffuse", diffuseColor);
	shader.setVec3("pointLights[" + pointLightNum + "].specular", specular);
	shader.setFloat("pointLights[" + pointLightNum + "].constant", attenuationConstant);
	shader.setFloat("pointLights[" + pointLightNum + "].linear", attenuationLinear);
	shader.setFloat("pointLights[" + pointLightNum + "].quadratic", attenuationQuadratic);
}

//sets spotlight
void setSpotLight(Shader shader, glm::vec3 color, glm::vec3 specular, float attenuationConstant, float attenuationLinear, float attenuationQuadratic, float cutOff, float outerCutOff) {
	glm::vec3 diffuseColor = color * glm::vec3(0.5f);
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);

	shader.setVec3("flashlight.direction", camera.Front);
	shader.setVec3("flashlight.position", camera.Position);
	shader.setVec3("flashlight.ambient", ambientColor);
	shader.setVec3("flashlight.diffuse", diffuseColor);
	shader.setVec3("flashlight.specular", specular);
	shader.setFloat("flashlight.constant", attenuationConstant);
	shader.setFloat("flashlight.linear", attenuationLinear);
	shader.setFloat("flashlight.quadratic", attenuationQuadratic);
	shader.setFloat("flashlight.cutOff", cutOff);
	shader.setFloat("flashlight.outerCutOff", outerCutOff);
}