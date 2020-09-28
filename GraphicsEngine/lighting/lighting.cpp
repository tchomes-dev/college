#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader/Shader.h>
#include <Camera/Camera.h>
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

using namespace std;

//settings
//---------------------
const unsigned int width = 1280;
const unsigned int height = 720;

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
unsigned int loadTexture(const char* filePath);

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

	//build and compile our shader program
	//-----------------------------------
<<<<<<< Updated upstream
	Shader cubeShader("object data/cube/cubeColor.vs", "object data/cube/cubeColor.fs");
	Shader lampShader("object data/lamp/lampShader.vs", "object data/lamp/lampShader.fs");
=======
	Shader ourShader("C:/Users/Tony/Dropbox/Model_Data/backpack/backpack.vs", "C:/Users/Tony/Dropbox/Model_Data/backpack/backpack.fs");
	Shader lampShader("C:/Users/Tony/Dropbox/Model_Data/lamp/lampShader.vs", "C:/Users/Tony/Dropbox/Model_Data/lamp/lampShader.fs");

	//load model (replace with path to obj file)
	Model backpack("C:/Users/Tony/Dropbox/Model_Data/sponza/sponza.obj");
	Model lamp("C:/Users/Tony/Dropbox/Model_Data/lamp/lamp.obj");

	//Light setup
	Light light(ourShader, camera);
>>>>>>> Stashed changes

	//set up vertex data (and buffer(s)) and configure vertex attributes
	//-----------------------------------
	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};
	glm::vec3 pointLightColors[] = {
		glm::vec3(1.0f),             //white
		glm::vec3(0.0f, 0.0f, 1.0f), //blue
		glm::vec3(1.0f,0.0f,0.0f),   //red
		glm::vec3(0.0f,1.0f,0.0f)    //green
	};
	unsigned int VBO, VAO, lightVAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenVertexArrays(1, &lightVAO);

	// .. :: Initialization Code :: ..
	//1. bind Container Object
	glBindVertexArray(VAO);
	//copy vertices array in a vertex buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//position setup
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//normals setup
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	//texture setup
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//load and create a diffuse map
	//------------------------------------
	unsigned int diffuseMap = loadTexture("C:/Users/Tony/Dropbox/Projects/C++ Projects/lighting/container2.png");

	//load and create a specular map
	//------------------------------------
	unsigned int specularMap = loadTexture("C:/Users/Tony/Dropbox/Projects/C++ Projects/lighting/container2_specular.png");

	//tell OpenGL for each sampler which texture unit it belongs to
	cubeShader.use();
	cubeShader.setInt("material.diffuse", 0);
	cubeShader.setInt("material.specular", 1);

	//2. bind Lamp Object
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//position setup
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); 

	//render loop
	while (!glfwWindowShouldClose(window)) {
		//per-frame time logic
		float currentFrame = glfwGetTime() * 3;
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glm::vec3 pointLightPositions[] = {
		glm::vec3(sin(currentFrame) * 10.0f,  0.0f,  4.0f + -cos(currentFrame) * 10.0f),
		glm::vec3(2.3f, 3.3f -sin(currentFrame) * 10.0f, -4.0f + cos(currentFrame) * 10.0f),
		glm::vec3(-4.0f + sin(currentFrame) * 10.0f,  2.0f, -5.0f + -cos(currentFrame) * 10.0f),
		glm::vec3(5.0f - sin(currentFrame) * 10.0f,  0.0f, -3.0f + cos(currentFrame) * 10.0f)
		};

		//input
		processInput(window);

		//rendering commands
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//binding texture(s)
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);

		//define model, camera and projection matrices
		//-----------------------------------
		cubeShader.use();
		glm::mat4 view = camera.GetViewMatrix();
<<<<<<< Updated upstream
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.1f, 100.0f);
		cubeShader.setVec3("viewPos", camera.Position);
		cubeShader.setMat4("view", view);
		cubeShader.setMat4("projection", projection);
		cubeShader.setVec3("viewPos", camera.Position);
		//configure shading and draw container
		//-----------------------------------
	    //container material settings
		cubeShader.setVec3("material.specular", glm::vec3(0.5f));
		cubeShader.setFloat("material.shininess", 64.0f);
		//directional light settings
		setDirectionalLight(cubeShader, glm::vec3(0.0f), glm::vec3(0.0f, 2.0f, -3.0f), glm::vec3(1.0f));
		//point light settings
		for (int i = 0; i < sizeof(pointLightPositions) / sizeof(pointLightPositions[0]); i++) {
			setPointLight(cubeShader, pointLightColors[i], pointLightPositions[i], glm::vec3(1.0f), 1.0f, 0.09f, 0.032f, i);
		}
		//flashlight settings
		setSpotLight(cubeShader, flashlightColor, glm::vec3(1.0f), 1.0f, 0.09f, 0.032f, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f)));

		//send model matricies to shaders
		for (int i = 0; i < sizeof(cubePositions)/sizeof(cubePositions[0]); i++) {
			//container model translation and scaling
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));
			cubeShader.setMat4("model", model);
			cubeShader.setFloat("time", glfwGetTime());
			//render container
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
=======
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.1f, 100.0f);
		ourShader.setMat4("view", view);
		ourShader.setMat4("projection", projection);

		//model translation and scaling			
		glm::mat4 model = glm::mat4(1.0f);
<<<<<<< Updated upstream
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f));
=======
		model = glm::translate(model, glm::vec3(0.0f, -5.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.02f));
>>>>>>> Stashed changes
		//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		ourShader.setMat4("model", model);

		//lighting
		for (int i = 0; i < 4; i++) {
			light.setPointLight(pointLightColors[i], pointLightPositions[i], glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09, 0.032, i);
>>>>>>> Stashed changes
		}

		//draw lamp and set colors
		//-----------------------------------
		lampShader.use();
		//send model, view and projections matricies to shaders
		lampShader.setMat4("projection", projection);
		lampShader.setMat4("view", view);
		for (int i = 0; i < sizeof(pointLightPositions) / sizeof(pointLightPositions[0]); i++) {
			//lamp model color
			lampShader.setVec3("color", pointLightColors[i]);
			//lamp model translation and scaling
			glm::mat4 lightModel = glm::mat4(1.0f);
			lightModel = glm::mat4(1.0f);
			lightModel = glm::translate(lightModel, pointLightPositions[i]);
			lightModel = glm::scale(lightModel, glm::vec3(0.25f));
			lampShader.setMat4("model", lightModel);
			//render lamp
			glBindVertexArray(lightVAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);
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

//takes in file path and utilizes stbi to load a texture with repeat wrapping and linear filtering
//TODO: change for greater options in the future like choice of wrapping and filtering
unsigned int loadTexture(const char * filePath) {
	unsigned int textureID;
	glGenTextures(1, &textureID);

	//load and generate texture
	int width, height, nrChannels;

	unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);
	if (data) {
		GLenum format = 0;

		switch (nrChannels) {
			case 1:
				format = GL_RED;
			case 3:
				format = GL_RGB;
			case 4:
				format = GL_RGBA;
		}

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		//set texture wrapping options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//set texture filtering options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else {
		std::cout << "Failed to load diffuseMap" << std::endl;
	}
	stbi_image_free(data);

	return textureID;
}