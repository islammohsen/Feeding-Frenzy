#include "Game.h"

Game::Game()
{
}

void Game::Initialize()
{
	ModelLoader::ImportModels();
	renderer = new Renderer();
	textureShader = new Shader(textureShaderFileName);
	basicShader = new Shader(basicShaderFileName);
	level = new Level(0);
	Fishes.push_back(new Fish(1.0f, 1.0f, 200.0f, 150.0f, 75.0f, 50.0f, 1.0f, "21856_Koi_v1", "Resources/Textures/Fish/TropicalFish01.jpg"));
	view_matrix = glm::lookAt(
		glm::vec3(0.0f, 0.0f, 720.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
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
