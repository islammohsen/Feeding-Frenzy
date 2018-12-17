#include <iostream>

#include <gL\glew.h>
#include <gl\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "Game.h"

using namespace std;

const float PI = acos(-1);

#define RED 1.0f, 0.0f, 0.0f
#define GREEN 0.0f, 1.0f, 0.0f
#define BLUE 0.0f, 0.0f, 1.0f
#define BLACK 0.0f, 0.0f, 0.0f

Game *game;

int keyPressed = -1;

void SpecialKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS || GLFW_REPEAT)
		keyPressed = key;
	if (keyPressed == GLFW_KEY_Q)
		game->ourHero->playerCamera.Yaw(10.0f);
	if (keyPressed == GLFW_KEY_E)
		game->view_matrix *= glm::rotate(-10.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	if (keyPressed == GLFW_KEY_W)
		game->ourHero->playerCamera.Walk(20.0f);
	if (keyPressed == GLFW_KEY_S)
		game->ourHero->playerCamera.Walk(-20.0f);

}

glm::vec2 normalize(glm::vec2 v)
{
	float mat[3][3] = { 
		{ 2.0f / (1024.0f - 0.0f), 0.0f, -((1024.0f + 0.0f) / (1024.0f - 0.0f)) },
		{ 0.0f, 2.0f / (720.0f - 0.0f), -((720.0f + 0.0f) / (720.0f - 0.0f)) },
		{ 0.0f, 0.0f, 1.0f } 
	};
	glm::vec3 vv = glm::vec3(v, 1.0f);
	glm::vec3 ans;
	for (int i = 0; i < 3; i++)
	{
		ans[i] = 0;
		for (int j = 0; j < 3; j++)
			ans[i] += mat[i][j] * vv[j];
	}
	return glm::vec2(ans.x, ans.y);
}

void MouseMoved(GLFWwindow* window, double MouseXPos, double MouseYPos) {
	glm::vec2 v = normalize(glm::vec2(MouseXPos, MouseYPos));
	v.x *= 1024;
	v.y *= 720.0f;
	v.y *= -1;
	game->ourHero->GoTo(game->ourHero->currentXPos + v.x, game->ourHero->currentYPos + v.y);
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

	glfwSetCursorPos(window, 1024.0f / 2.0f, 720.0f / 2.0f);
	glfwSetCursorPosCallback(window, &MouseMoved);
	

	game = new Game();
	game->Initialize();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */

		game->Update();
		game->CheckCollision();
		game->Draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}