#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <gL\glew.h>
#include <gl\glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

using namespace std;

#define RED 1.0f, 0.0f, 0.0f
#define GREEN 0.0f, 1.0f, 0.0f
#define BLUE 0.0f, 0.0f, 1.0f
#define BLACK 0.0f, 0.0f, 0.0f

string shaderFileName = "Basic.shader";

int keyPressed = -1;
double MouseXPos = -1.0;
double MouseYPos = -1.0;

void SpecialKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS || GLFW_REPEAT)
		keyPressed = key;
}

void MouseClicked(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_MOUSE_BUTTON_LEFT)
		glfwGetCursorPos(window, &MouseXPos, &MouseYPos);
}

int main()
{
	GLFWwindow* window;


	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1024, 720, "Hello World", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK){
		cout << "ERROR!";
		return 0;
	}

	float points1[] = {
		0.0f, 0.0f, 0.0f, RED,
		100.0f, 0.0f, 0.0f, RED,
		100.0f, 100.0f, 0.0f, RED,
		0, 100.0f, 0.0f, RED,
	};

	unsigned int indices1[] = {
		0, 1, 2, 
		2, 3, 0,
	};

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	VertexArray *va1 = new VertexArray();
	VertexBuffer *square = new VertexBuffer(points1, sizeof(points1));
	VertexBufferLayout layout1;
	layout1.push<float>(3);
	layout1.push<float>(3);
	va1->AddBuffer(*square, layout1);
	IndexBuffer *ib1 = new IndexBuffer(indices1, sizeof(indices1) / sizeof(unsigned int));
	
	Shader *shader = new Shader(shaderFileName);

	Renderer *renderer = new Renderer();

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetKeyCallback(window, &SpecialKeyPressed);
	glfwSetMouseButtonCallback(window, &MouseClicked);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		renderer->Clear();

		glm::mat4 proj = glm::ortho(0.0f, 1024.0f, 0.0f, 720.0f);
		glm::mat4 view = glm::mat4(1);
		glm::mat4 model = glm::mat4(1);

		shader->Bind();
		shader->SetUniformMat4f("u_MVP", proj * view * model);

		//drawing
		va1->Bind();
		renderer->Draw(va1, ib1, shader, GL_TRIANGLES);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	delete shader;
	delete va1;
	delete square;
	delete ib1;
	delete renderer;

	glfwTerminate();
	return 0;
}