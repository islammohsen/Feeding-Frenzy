#include "Game.h"

Game::Game()
{
}

bool PointInPolygon(const vector<glm::vec2> &p, glm::vec2 q) {
	bool c = 0;
	for (int i = 0; i < p.size(); i++) {
		int j = (i + 1) % p.size();
		if ((p[i].y <= q.y && q.y < p[j].y ||
			p[j].y <= q.y && q.y < p[i].y) &&
			q.x < p[i].x + (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y))
			c = !c;
	}
	return c;
}


bool Game::Collision(vector<glm::vec2> source, glm::vec2 mouth, vector<glm::vec2> target)
{
	return PointInPolygon(target, mouth);
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
	while (mainBot.getFishCount())
	{
		bots.push_back(mainBot.initialRandomPosition("21856_Koi_v1", "Resources/Textures/Fish/TropicalFish01.jpg"));
		mainBot.setFishCount(mainBot.getFishCount() - 1);
	}
}

void Game::Draw()
{
	renderer->Clear();

	glm::mat4 proj = glm::perspective(45.0f, 1024.0f / 720.0f, 0.1f, 10000.0f);
	glm::mat4 view = view_matrix;

	level->DrawBackground(renderer, textureShader, view, proj);
	for (auto &fish : Fishes)
		fish->Draw(renderer, textureShader, view, proj);
	for (auto &currentBot : bots)
	{
		currentBot->generateNextPoint();
		currentBot->getGoing();
		currentBot->fish->Draw(renderer, textureShader, view, proj);
	}
}

Game::~Game()
{
}
