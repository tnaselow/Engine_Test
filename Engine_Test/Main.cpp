#define GLEW_STATIC

#include <iostream>
#include <GL\glew.h>
#include "GLFW\glfw3.h"
#include "SOIL\SOIL.h"
#include "Shader.h"
#include "Sapph\Matrix4.h"
#include "Sapph\Vector3.h"
#include "FPSCamera.h"

// added comment 
// HELOOO FROM THE OUTTTSIDDDE
// SEND BACK TO Main 
// send back to client

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);

GLuint vertShader;
GLuint fragShader;

GLuint VAO1;
GLuint VAO2;

FPSCamera cam(0, 0, 3);

float deltaTime;
float lastFrame;
bool keys[1024];


void triangleInit()
{
	GLfloat vertices1[] = {
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

	GLfloat vertices2[] =
	{
		0.9f,  0.9f, 0.0f,  1.0f, 1.0f,// Top Right
		0.9f, 0.5f, 0.0f,   1.0f, 0.0f,// Bottom Right
		0.0f, 0.5f, 0.0f,   0.0f, 0.0f,// Bottom Left
		0.0f,  0.9f, 0.0f,  0.0f, 1.0f// Top Left 
	};

	GLuint indices1[] = {  // Note that we start from 0!
		0, 1, 3,   // First Triangle
		1, 2, 3    // Second Triangle
	};

	GLuint indicies2[] =
	{
		0, 1, 3,   // First Triangle
		1, 2, 3
	};

	GLuint VBO1, EBO1;
	GLuint VBO2, EBO2;

	glGenVertexArrays(1, &VAO1);
	glGenVertexArrays(1, &VAO2);

	glGenBuffers(1, &VBO1);
	glGenBuffers(1, &EBO1);

	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO2);

	glBindVertexArray(VAO2);

		glBindBuffer(GL_ARRAY_BUFFER, VBO2);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies2), indicies2, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);


		glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindVertexArray(VAO1);

		glBindBuffer(GL_ARRAY_BUFFER, VBO1);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}


int main(int args, char **argv)
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Practice", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Could not create GLFW window!" << std::endl;
		glfwTerminate();
		abort();
	}

	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
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



	//GLuint shader = shadersInit();
	Shader shader("../shaders/vert.shader", "../shaders/frag.shader");
	triangleInit();

	Matrix4 mat;
	//Matrix4 view;
	Matrix4 persp;
	Matrix4 temp;
	
	persp.SetPerspective(45.0f, static_cast<float>(WINDOW_WIDTH) / WINDOW_HEIGHT, 0.1f, 100);
	//persp.SetOrtho(-400 , 400, -300, 300, -1.0f, 1.0f);
	
	//mat.Translate(400, 0, 0);
	//mat.RotateDeg(45.0f);
	//mat.Translate(-400.0f, 300.0f, 0);
	//mat.Scale(100);
	//mat = temp.RotateDeg(45.0f) * mat;

	//view.Translate(0, 0, 3.0f);
	//mat = mat * mat2.Scale(2.0f);
	//mat2.Translate(.5, .5, 1);

	GLuint transform = glGetUniformLocation(shader.Program, "transform");
	GLint xOffset = glGetUniformLocation(shader.Program, "xOffset");
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
	
	Vector3 cubePositions[] = {
		Vector3(0.0f,  0.0f,  0.0f),
		Vector3(2.0f,  5.0f, -15.0f),
		Vector3(-1.5f, -2.2f, -2.5f),
		Vector3(-3.8f, -2.0f, -12.3f),
		Vector3(2.4f, -0.4f, -3.5f),
		Vector3(-1.7f,  3.0f, -7.5f),
		Vector3(1.3f, -2.0f, -2.5f),
		Vector3(1.5f,  2.0f, -2.5f),
		Vector3(1.5f,  0.2f, -1.5f),
		Vector3(-1.3f,  1.0f, -1.5f)
	};

	
	while (!glfwWindowShouldClose(window))
	{

		float currentTime = static_cast<float>(glfwGetTime());
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
		GLfloat time = (float)glfwGetTime();
		GLfloat offset = ((float)sin(time) / 2) + 0.5f;
		shader.Use();
		//cam.SetDir(Vector3(cos(time) * cos(time), 0, sin(time) * sin(time)));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, true, persp.GetMatrixData());
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, true, cam.GetViewMatrix().GetMatrixData());
		//mat.Translate(0, 0, sin(time));
		//mat.Scale(time);
		//mat.Translate(0, 0, sin(time));
		//cam.SetPos(Vector3(0, 0, time * 0.1f));
		temp.SetToIdentity();
		mat = mat * temp.RotateDeg(sin(time) * 30 * deltaTime, ROT_AXIS::X_AXIS);
		temp.SetToIdentity();
		mat = mat * temp.RotateDeg(sin(time) * 30 * deltaTime);
		//glUseProgram(shader.Program);
		glUniform1f(xOffset, offset);
		glUniform1f(glGetUniformLocation(shader.Program, "blendFactor"), offset);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(shader.Program, "ourTexture"), 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(shader.Program, "ourTexture2"), 1);

		for (int i = 0; i < 10; i++)
		{
			mat.Translate(cubePositions[i]);
			glUniformMatrix4fv(transform, 1, true, mat.GetMatrixData());
			glBindVertexArray(VAO1);
			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//glBindVertexArray(VAO2);
		//glUniformMatrix4fv(transform, 1, true, mat2.GetMatrixData());
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0);

		glfwSwapBuffers(window);

		if (keys[GLFW_KEY_W])
			cam.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
		if (keys[GLFW_KEY_S])
			cam.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
		if (keys[GLFW_KEY_A])
			cam.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
		if (keys[GLFW_KEY_D])
			cam.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);

		cam.Yaw += deltaTime * 10;
		cam.UpdateCameraVectors();
		cam.UpdateMatrix();
		std::cout << cam.GetViewMatrix() << std::endl;
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

	//cam.ProcessMouseMovement(xoffset, yoffset);
}