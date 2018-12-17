#include "Game.h"
#include "Hero.h"

void Game::Attack()
{
	
}

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


bool Game::Collision(glm::vec2 mouth, vector<glm::vec2> target)
{
	return PointInPolygon(target, mouth);
}

void Game::Initialize()
{
	time = glfwGetTime();
	ModelLoader::ImportModels();
	renderer = new Renderer();
	textureShader = new Shader(textureShaderFileName);
	basicShader = new Shader(basicShaderFileName);
	level = new Level(0);
	view_matrix = glm::lookAt(
		glm::vec3(0.0f, 0.0f, 720.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
	ourHero = new Hero(0.0f, 200.0f, 512.0f, 120.0f, 40.0f, 30.0f, 3.0f, 2, "3d-model", "Resources/Textures/Fish/TropicalFish10.jpg");
	for (int i = 0; i < level->getFishType1Counter(); i++)
		bots.push_back(new Ai(60.0f, 20.0f, 15.0f, 1.0f, 1, "21856_Koi_v1", "Resources/Textures/Fish/TropicalFish01.jpg"));
	for (int i = 0; i < level->getFishType2Counter(); i++)
		bots.push_back(new Ai(120.0f, 40.0f, 30.0f, 1.0f, 2, "21856_Koi_v1", "Resources/Textures/Fish/TropicalFish02.jpg"));
	for (int i = 0; i < level->getFishType3Counter(); i++)
		bots.push_back(new Ai(180.0f, 80.0f, 45.0f, 1.0f, 3, "21856_Koi_v1", "Resources/Textures/Fish/TropicalFish03.jpg"));
}

void Game::Draw()
{
	renderer->Clear();

	glm::mat4 proj = ourHero->playerCamera.GetProjectionMatrix();
	glm::mat4 view = ourHero->playerCamera.GetViewMatrix();

	level->DrawBackground(renderer, textureShader, view, proj);
	ourHero->Draw(renderer, textureShader, view, proj);
	for (auto &currentBot : bots)
		currentBot->Draw(renderer, textureShader, view, proj);
}

void Game::Update()
{
	float newTime = glfwGetTime();

	if (newTime - time >= 2) {
		cout << "attack triggered\n";
		//Attack();
		time = newTime;
	}
	ourHero->getGoing();
	for (auto &currentBot : bots)
		currentBot->getGoing();
}

void Game::CheckCollision()
{
	set<int> Remove;
	for (int i = 0; i < bots.size(); i++)
	{
		if (bots[i]->GetType() >= ourHero->GetType())
			continue;
		if (Collision(ourHero->GetMouth(), bots[i]->GetCollisionPolygon())) {
			Remove.insert(i);
			ourHero->Eat();
		}
	}
	bool heroDead = false;
	for (int i = 0; i < bots.size(); i++)
	{
		glm::vec2 mouth = bots[i]->GetMouth();
		for (int j = 0; j < bots.size(); j++)
		{
			if (i == j || bots[j]->GetType() >= bots[i]->GetType())
				continue;
			if (Collision(mouth, bots[j]->GetCollisionPolygon()))
				Remove.insert(j);
		}
		if (bots[i]->GetType() > ourHero->GetType() && Collision(mouth, ourHero->GetCollisionPolygon()))
			heroDead = true;
	}
	if (heroDead)
	{
		delete ourHero;
		ourHero = new Hero(0.0f, 200.0f, 512.0f, 120.0f, 40.0f, 30.0f, 3.0f, 2, "3d-model", "Resources/Textures/Fish/TropicalFish10.jpg");
	}
	vector<Ai*> copy = bots;
	bots.clear();
	int t[4] = {};
	for (int i = 0; i < copy.size(); i++)
	{
		if (Remove.find(i) != Remove.end())
		{
			t[copy[i]->GetType()]++;
			delete copy[i];
		}
		else
			bots.push_back(copy[i]);
	}
	for (int i = 1; i < 4; i++)
	{
		while (t[i]--)
		{
			if(i == 1)
				bots.push_back(new Ai(60.0f, 30.0f, 15.0f, 1.0f, 1, "21856_Koi_v1", "Resources/Textures/Fish/TropicalFish01.jpg"));
			else if(i == 2)
				bots.push_back(new Ai(120.0f, 60.0f, 30.0f, 1.0f, 2, "21856_Koi_v1", "Resources/Textures/Fish/TropicalFish02.jpg"));
			else
				bots.push_back(new Ai(180.0f, 90.0f, 45.0f, 1.0f, 3, "21856_Koi_v1", "Resources/Textures/Fish/TropicalFish03.jpg"));
		}
	}
}

Game::~Game()
{
}
