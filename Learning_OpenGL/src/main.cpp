#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "graphics/Shader.h"

#define _OPEN_SYS_ITOA_EXT
#include <stdio.h>
#include <stdlib.h>

#include "io/Keyboard.h";
#include "io/Joystick.h";
#include "io/Mouse.h";
#include "io/Camera.h";
#include "io/Screen.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(double dt);

//using namespace std;

const int INFOLOGSIZE= 600;

float mixVal = 0.5f;
glm::mat4 transform = glm::mat4(1.0f);
//Joystick mainJ(0);

//glm::mat4 mouseTransform = glm::mat4(1.0f);

unsigned int SCR_WIDTH = 800, SCR_HEIGHT = 600;

Screen screen;

//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
Camera cameras[2] = {
	Camera(glm::vec3(0.0f, 0.0f, 3.0f)),
	Camera(glm::vec3(0.0f, 0.0f, 10.0f))
};
int activeCam = 0;
float x, y, z;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main() {
	std::cout << "Hello, world" << std::endl;

	int success;
	char infoLog[INFOLOGSIZE];
	
	//initiation of opengl
	glfwInit();

	//telling computer that is openGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//if compiling on mac then
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // DEBUG

	//creating window
	//set focus glfw to this window
	if (!screen.init()) {
		std::cout << "Could not create window." << std::endl;
		glfwTerminate();
		return -1;
	}

	//glad allows us to manage openGL function and classes
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	//position of the window
	//everytime window size change it fit things inside
	screen.setParameters();

	/*
		shaders
	*/

	//compile vertex shader
	Shader shader("assets/object.vs", "assets/object.fs");

	//to not repeating last and first triangle vertex, we can bind with ints which are indicators

	//vertices of rectangle
	//float vertices[] = {
	//	// position				colors					picture position on it
	//	-0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 0.5f,		0.0f, 0.0f,
	//	-0.5f,  0.5f, 0.0f,		0.5f, 1.0f, 0.75f,		0.0f, 1.0f,
	//     0.5f, -0.5f, 0.0f,		0.6f, 1.0f, 0.2f,		1.0f, 0.0f,
	//	 0.5f,  0.5f, 0.0f,		1.0f, 0.2f, 1.0f,		1.0f, 1.0f
	//};

	//unsigned int indices[] = {
	//	0, 1, 2, // first triangle
	//	3, 1, 2  //second triangle
	//};
	
	float vertices[] = {

//	position			  tex coordinates
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	
	//number of vertices
	int noVertices = 6;

	//type of primitive
	GLenum primitive = GL_TRIANGLES;

	//VAO,VBO
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	//bind VAO
	glBindVertexArray(VAO);

	//bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//set up EBO
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	//atrrb pointer points every set of data what is what (position)
	glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//attrib for colors
	/*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);*/

	//attrib for texture coordinates
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//TEXTURES

	unsigned int texture1, texture2;

	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	//x
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	//y

	//type of loading picture colors
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	

	//loading image
	int width, height, nChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("assets/supra.jpg", &width, &height, &nChannels, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	data = stbi_load("assets/Moon.jpg", &width, &height, &nChannels, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	shader.activate();
	shader.setInt("texture1", 0);
	shader.setInt("texture2", 1);

	//TRANSFORMATING OBJECT 2D
	//rotating object and scaling
	//glm::mat4 trans = glm::mat4(1.0f);
	//trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	////trans = glm::scale(trans, glm::vec3(0.5f, 1.5f, 0.5f));
	//shader.activate();
	//shader.setMat4("transform", trans);

	//joysick
	//mainJ.update();
	/*if (mainJ.isPresent()) {
		std::cout << mainJ.getName() << " is present." << std::endl;
	}*/
	
	//MAIN WHILELOOP
	while (!screen.shouldClose()) {
		

		//std::cout << (double)Mouse::getDX() << " , " << (double)Mouse::getDY() << std::endl;
		double currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		//User input
		processInput(deltaTime);
		
		//clearing and setting background
		screen.update();

		//binding textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		//rotating object over time
		/*trans = glm::rotate(trans, glm::radians(0.01f), glm::vec3(0.0f, 0.0f, 1.0f));
		shader.activate();
		shader.setMat4("transform", trans);*/

		//draw shapes
		glBindVertexArray(VAO);

		//creating transformation for screen (3D camera)
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-55.0f), glm::vec3(0.5f, 0.5f, 0.5f));
		view = cameras[activeCam].getViewMatrix();
		//view = glm::translate(view, glm::vec3(-x, -y, -z));
		//FOV
		projection = glm::perspective(glm::radians(cameras[activeCam].getZoom()), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);

		//activating current shader
		shader.activate();

		//manipulating uniform variable which is in shadercode
		shader.setFloat("mixVal", mixVal);
		//shader.setMat4("transform", transform);
		shader.setMat4("model", model);
		shader.setMat4("view", view);
		shader.setMat4("projection", projection);

		//
		//shader.setMat4("transform", transform);

		//first triangle
		//glDrawElements(primitive, 6, GL_UNSIGNED_INT, 0);

		//drawinf without elements
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//glUseProgram(shaderPrograms[1]);
		//glDrawElements(primitive, noVertices/2, GL_UNSIGNED_INT, (void*)(3*sizeof(unsigned int)));

		//generates next frame while previous frame is being displayed
		screen.newFrame();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
}

void processInput(double dt) {
	if (Keyboard::key(GLFW_KEY_ESCAPE)) {
		screen.setShouldClose(true);
	}

	//if pressed changes value every frame
	//if (Keyboard::key(GLFW_KEY_UP)) {
	//	mixVal += 0.001f;
	//	//std::cout << mixVal;
	//	if (mixVal > 1.0f) mixVal = 1.0f;
	//}
	//if (Keyboard::key(GLFW_KEY_DOWN)) {
	//	mixVal -= 0.001f;
	//	//std::cout << mixVal;
	//	if (mixVal < 0.0f) mixVal = 0.0f;
	//}
	//if pressed changes value only once 

	float changeVal = 0.01f;
	if (Keyboard::keyWentUp(GLFW_KEY_UP)) {
		mixVal += 0.1f;
		//std::cout << mixVal;
		if (mixVal > 1.0f) mixVal = 1.0f;
	}
	if (Keyboard::keyWentDown(GLFW_KEY_DOWN)) {
		mixVal -= 0.1f;
		//std::cout << mixVal;
		if (mixVal < 0.0f) mixVal = 0.0f;
	}
	if (Keyboard::keyWentDown(GLFW_KEY_TAB)) {
		activeCam == 1 ? activeCam = 0 : activeCam = 1;
	}
	if (Keyboard::key(GLFW_KEY_W)) {
		cameras[activeCam].updateCameraPos(CameraDirection::FORWARD, dt);
	}
	if (Keyboard::key(GLFW_KEY_A)) {
		cameras[activeCam].updateCameraPos(CameraDirection::LEFT, dt);
	}
	if (Keyboard::key(GLFW_KEY_S)) {
		cameras[activeCam].updateCameraPos(CameraDirection::BACKWARD, dt);
	}
	if (Keyboard::key(GLFW_KEY_D)) {
		cameras[activeCam].updateCameraPos(CameraDirection::RIGHT, dt);
	}
	if (Keyboard::key(GLFW_KEY_SPACE)) {
		cameras[activeCam].updateCameraPos(CameraDirection::UP, dt);
	}
	if (Keyboard::key(GLFW_KEY_LEFT_SHIFT)) {
		cameras[activeCam].updateCameraPos(CameraDirection::DOWN, dt);
	}

	double dx = Mouse::getDX(), dy = Mouse::getDY();
	if (dx != 0 || dy != 0) {
		cameras[activeCam].updateCameraDirection(dx, dy);
	}

	double scrollDy = Mouse::getScrollDY();
	if (scrollDy != 0) {
		cameras[activeCam].updateCameraZoom(scrollDy);
	}

	//to develope
	//mainJ.update();
}