#define GLEW_STATIC

#include <iostream>
#include <GL\glew.h>
#include "GLFW\glfw3.h"
#include "SOIL\SOIL.h"
#include "Shader.h"
#include "Sapph\Matrix4.h"
#include "Sapph\Vector3.h"
#include "Camera.h"

// added comment 
// HELOOO FROM THE OUTTTSIDDDE
// SEND BACK TO Main 
// send back to client

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

GLuint vertShader;
GLuint fragShader;

GLuint VAO1, LightVAO;

Camera camera(0, 0, 3);
Matrix4 persp;

Vector3 lightPos(2, 3, -3);
Matrix4 lightMat;

float deltaTime;
float lastFrame;
bool keys[1024];


void triangleInit()
{
	GLfloat vertices1[] = {

		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f, 
		0.5f,  0.5f, -0.5f, 
		0.5f,  0.5f, -0.5f, 
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f, 
		0.5f,  0.5f,  0.5f, 
		0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		0.5f,  0.5f,  0.5f, 
		0.5f,  0.5f, -0.5f, 
		0.5f, -0.5f, -0.5f, 
		0.5f, -0.5f, -0.5f, 
		0.5f, -0.5f,  0.5f, 
		0.5f,  0.5f,  0.5f, 

		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f, 
		0.5f, -0.5f,  0.5f, 
		0.5f, -0.5f,  0.5f, 
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f, 
		0.5f,  0.5f,  0.5f, 
		0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f
	};

	GLuint VBO1, LightVBO;

	glGenVertexArrays(1, &VAO1);
	glGenVertexArrays(1, &LightVAO);

	glGenBuffers(1, &VBO1);
	glGenBuffers(1, &LightVBO);
	
	glBindVertexArray(VAO1);

		glBindBuffer(GL_ARRAY_BUFFER, VBO1);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindVertexArray(LightVAO);

		glBindBuffer(GL_ARRAY_BUFFER, LightVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid *)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}


int main(int args, char **argv)
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Practice", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Could not create GLFW window!" << std::endl;
		glfwTerminate();
		abort();
	}

	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize glew" << std::endl;
		abort();
	}

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);



	Shader shader("../shaders/vert.shader", "../shaders/frag.shader");
	
	triangleInit();

	Matrix4 mat;
	
	persp.SetPerspective(45.0f, static_cast<float>(WINDOW_WIDTH) / WINDOW_HEIGHT, 0.1f, 100);


	GLuint transform = glGetUniformLocation(shader.Program, "transform");
	
	int width, height;
	unsigned char *image = SOIL_load_image("../res/container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	//unsigned char *image = SOIL_load_image("../res/basic_tiles.png", &width, &height, 0, SOIL_LOAD_RGB);
	GLuint texture, texture2;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	//image = SOIL_load_image("../res/awesomeface.png", &width, &height, 0, SOIL_LOAD_RGB);
	image = SOIL_load_image("../res/basic_tiles.png", &width, &height, 0, SOIL_LOAD_RGB);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	Vector3 cubePos(0, 0, 0);

	Vector3 objColor;
	
	while (!glfwWindowShouldClose(window))
	{

		float currentTime = static_cast<float>(glfwGetTime());
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
		GLfloat time = (float)glfwGetTime();
		shader.Use();
		//cam.SetDir(Vector3(cos(time) * cos(time), 0, sin(time) * sin(time)));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, true, persp.GetMatrixData());
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, true, camera.GetViewMatrix().GetMatrixData());
		
		mat.RotateDeg(sin(time) * 30 * deltaTime, ROT_AXIS::X_AXIS);
		mat.RotateDeg(sin(time) * 30 * deltaTime);
		

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(shader.Program, "ourTexture"), 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(shader.Program, "ourTexture2"), 1);

		objColor = Vector3(1, 0, 0);
		glUniform3f(glGetUniformLocation(shader.Program, "objColor"), objColor.X, objColor.Y, objColor.Z);
		glBindVertexArray(VAO1);
		mat.Translate(cubePos);
		glUniformMatrix4fv(transform, 1, true, mat.GetMatrixData());
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		objColor = Vector3(1, 1, 1);
		glUniform3f(glGetUniformLocation(shader.Program, "objColor"), objColor.X, objColor.Y, objColor.Z);
		glBindVertexArray(LightVAO);
		lightMat.Translate(lightPos);
		glUniformMatrix4fv(transform, 1, true, lightMat.GetMatrixData());
		glDrawArrays(GL_TRIANGLES, 0, 36);


		glfwSwapBuffers(window);

		if (keys[GLFW_KEY_W])
			camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
		if (keys[GLFW_KEY_S])
			camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
		if (keys[GLFW_KEY_A])
			camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
		if (keys[GLFW_KEY_D])
			camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
	}


	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	glfwTerminate();
	return 0;
}


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{

	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

GLfloat lastX;
GLfloat lastY;
void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	GLfloat xoffset = static_cast<float>(xpos) - lastX;
	GLfloat yoffset = lastY - static_cast<float>(ypos);
	lastX = static_cast<float>(xpos);
	lastY = static_cast<float>(ypos);

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	float fov = camera.ProcessMouseScroll(static_cast<float>(yoffset));
	persp.SetPerspective(fov, static_cast<float>(WINDOW_WIDTH) / WINDOW_HEIGHT, 0.1f, 100);
}