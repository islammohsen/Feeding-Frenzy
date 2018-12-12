#include <iostream>

#include <gL\glew.h>
#include <gl\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "Game.h"

using namespace std;

#define RED 1.0f, 0.0f, 0.0f
#define GREEN 0.0f, 1.0f, 0.0f
#define BLUE 0.0f, 0.0f, 1.0f
#define BLACK 0.0f, 0.0f, 0.0f

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
	window = glfwCreateWindow(1024, 720, "Feeding Frenzy", NULL, NULL);

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

	Game *game = new Game();

	game->Initialize();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */

		game->Draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}