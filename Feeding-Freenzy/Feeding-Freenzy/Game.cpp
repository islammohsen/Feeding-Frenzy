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
	Fishes.push_back(new Fish(400.0f, 400.0f, 200.0f, 100.0f, 100.0f, 100.0f, 0.0f, "Resources/Textures/Fish/Fish-1.png"));
	
	vector<float> portalPoints = {
		700.0, 100.0f, 1.0f, 0.0f, 0.0f,
		700.0f, 300.0f, 1.0f, 0.0f, 1.0f,
		850.0f, 300.0f, 1.0f, 1.0f, 1.0f,
		850.0f, 100.0f, 1.0f, 1.0f, 0.0f
	};

	vector<unsigned int> portalIndex = { 0, 1, 2, 2, 3, 0 };
	portal = new Portal(portalPoints.data(), (portalPoints.size() * sizeof(float)), portalIndex.data(), portalIndex.size(), "Resources/Textures/Portal/Portal-1.png");
	
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


	level->DrawBoarder(renderer, basicShader, view, proj);
	level->DrawBackground(renderer, textureShader, view, proj);
	for (auto &fish : Fishes)
		fish->Draw(renderer, textureShader, view, proj);

	portal->Draw(renderer, textureShader, view, proj);
}

Game::~Game()
{
}
