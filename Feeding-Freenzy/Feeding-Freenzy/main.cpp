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
#include "Fish.h"
#include "Level.h"
#include "Portal.h"

using namespace std;

#define RED 1.0f, 0.0f, 0.0f
#define GREEN 0.0f, 1.0f, 0.0f
#define BLUE 0.0f, 0.0f, 1.0f
#define BLACK 0.0f, 0.0f, 0.0f

string textureShaderFileName = "Resources/shaders/TextureShader.shader";
string basicShaderFileName = "Resources/shaders/Basic.shader";

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

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //OpenGL version 3.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 3.3
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

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK){
		cout << "ERROR!";
		return 0;
	}

	GLCall(glEnable(GL_DEPTH_TEST)); 
	GLCall(glDepthFunc(GL_LESS));
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetKeyCallback(window, &SpecialKeyPressed);
	glfwSetMouseButtonCallback(window, &MouseClicked);

	Level *level = new Level(0);
	
	float points[] = {
		300.0f, 300.0f, 1.0f, 0.0f, 0.0f,
		300.0f, 500.0f, 1.0f, 0.0f, 1.0f,
		500.0f, 500.0f, 1.0f, 1.0f, 1.0f,
		500.0f, 300.0f, 1.0f, 1.0f, 0.0f
	};
	unsigned int index[] = { 0, 1, 2, 2, 3, 0 };
	
	vector<Fish*> F;
	F.push_back(new Fish(points, sizeof(points), index, 6, "Resources/Textures/Fish/Fish-1.png", 0.0f, 0.0f));
	Renderer *renderer = new Renderer();
	Shader *textureShader = new Shader(textureShaderFileName);
	Shader *basicShader = new Shader(basicShaderFileName);

	float portalPoints[] = {
		700.0, 100.0f, 1.0f, 0.0f, 0.0f,
		700.0f, 300.0f, 1.0f, 0.0f, 1.0f,
		850.0f, 300.0f, 1.0f, 1.0f, 1.0f,
		850.0f, 100.0f, 1.0f, 1.0f, 0.0f
	};
	unsigned int portalIndex[] = { 0, 1, 2, 2, 3, 0 };
	Portal *portal = new Portal(portalPoints, sizeof(portalPoints), portalIndex, 6, "Resources/Textures/Portal/Portal-1.png");

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		renderer->Clear();

		glm::mat4 proj = glm::ortho(0.0f, 1024.0f, 0.0f, 720.0f);
		glm::mat4 view = glm::mat4(1);
		level->DrawBoarder(renderer, basicShader, view, proj);

		level->DrawBackground(renderer, textureShader, view, proj);
		for (auto &x : F)
			x->Draw(renderer, textureShader, view, proj);
		
		portal->Draw(renderer, textureShader, view, proj);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	delete renderer;

	glfwTerminate();
	return 0;
}