#include "Game.h"

Game::Game()
{
}

void Game::Initialize()
{

	renderer = new Renderer();
	textureShader = new Shader(textureShaderFileName);
	basicShader = new Shader(basicShaderFileName);
	level = new Level(0);
	Fishes.push_back(new Fish(1.0f, 1.0f, 600.0f, 300.0f, 300.0f, 500.0f, 1.0f, "Resources/objects/TropicalFish02.obj", "Resources/Textures/Fish/TropicalFish02.jpg"));
	Fishes[0]->rotate(90.0f, 0.0f, 1.0f, 0.0f);
	view_matrix = glm::lookAt(
		glm::vec3((1024.0f / 2.0f), (720.0f / 2.0f), 720.0f),
		glm::vec3((1024.0f / 2.0f), (720.0f / 2.0f), -1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
}

void Game::Draw()
{
	renderer->Clear();

	glm::mat4 proj = glm::perspective(45.0f, 1024.0f / 720.0f, 0.1f, 10000.0f);
	glm::mat4 view = view_matrix;

	level->DrawBackground(renderer, textureShader, view, proj);
	for (auto &fish : Fishes)
		fish->Draw(renderer, textureShader, view, proj);
}

Game::~Game()
{
}
