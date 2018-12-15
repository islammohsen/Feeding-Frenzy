#include "Game.h"
#include "Hero.h"

void Game::Attack()
{
	for (auto &currenBot1 : botsType3)
	{
		bool f = 1;
		for (auto &currenBot2 : botsType2)
		{
			glm::vec2 points = currenBot2->GetPosition();
			if (currenBot1->pointInRange(points, 400.0f))
			{
				currenBot1->specificAttack(points);
				f = 1;
				break;
			}
		}
		if (f)
			continue;
		for (auto &currenBot2 : botsType1)
		{
			glm::vec2 points = currenBot2->GetPosition();
			if (currenBot1->pointInRange(points, 400.0f))
			{
				currenBot1->specificAttack(points);
				break;
			}
		}
	}
	for (auto &currenBot1 : botsType2)
	{
		for (auto &currenBot2 : botsType1)
		{
			glm::vec2 points = currenBot2->GetPosition();
			if (currenBot1->pointInRange(points, 400.0f))
			{
				currenBot1->specificAttack(points);
				break;
			}
		}
	}
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
	ourHero = new Hero(0.0f, 0.0f, 512.0f, 120.0f, 60.0f, 30.0f, 1.0f, "21856_Koi_v1", "Resources/Textures/Fish/TropicalFish06.jpg");
	for (int i = 0; i < 5; i++)
		botsType1.push_back(new Ai(60.0f, 30.0f, 15.0f, 1.0f, "21856_Koi_v1", "Resources/Textures/Fish/TropicalFish01.jpg"));
	for (int i = 0; i < 5; i++)
		botsType2.push_back(new Ai(120.0f, 60.0f, 30.0f, 1.0f, "21856_Koi_v1", "Resources/Textures/Fish/TropicalFish02.jpg"));
	for (int i = 0; i < 5; i++)
		botsType3.push_back(new Ai(180.0f, 90.0f, 45.0f, 1.0f, "21856_Koi_v1", "Resources/Textures/Fish/TropicalFish03.jpg"));

}

void Game::Draw()
{
	renderer->Clear();

	glm::mat4 proj = ourHero->playerCamera.GetProjectionMatrix();
	glm::mat4 view = ourHero->playerCamera.GetViewMatrix();

	level->DrawBackground(renderer, textureShader, view, proj);
	ourHero->Draw(renderer, textureShader, view, proj);
	for (auto &currentBot : botsType1)
	{
		currentBot->Draw(renderer, textureShader, view, proj);
	}
	for (auto &currentBot : botsType2)
	{
		currentBot->Draw(renderer, textureShader, view, proj);
	}
	for (auto &currentBot : botsType3)
	{
		currentBot->Draw(renderer, textureShader, view, proj);
	}
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
	for (auto &currentBot : botsType1)
	{
		currentBot->getGoing();
	}
	for (auto &currentBot : botsType2)
	{
		currentBot->getGoing();
	}
	for (auto &currentBot : botsType3)
	{
		currentBot->getGoing();
	}
}

void Game::CheckCollision()
{
	for (int i = 0; i < botsType3.size(); i++)
	{
		for (int j = 0; j < botsType2.size(); j++)
		{
			if (Collision(botsType3[i]->GetMouth(), botsType2[j]->GetCollisionPolygon()))
			{
				delete botsType2[j];
				botsType2.erase(botsType2.begin() + j);
				j--;
			}
		}
		for (int j = 0; j < botsType1.size(); j++)
		{
			if (Collision(botsType3[i]->GetMouth(), botsType1[j]->GetCollisionPolygon()))
			{
				delete botsType1[j];
				botsType1.erase(botsType1.begin() + j);
				j--;
			}
		}
	}
	for (int i = 0; i < botsType2.size(); i++)
	{
		for (int j = 0; j < botsType1.size(); j++)
		{
			if (Collision(botsType2[i]->GetMouth(), botsType1[j]->GetCollisionPolygon()))
			{
				delete botsType1[j];
				botsType1.erase(botsType1.begin() + j);
				j--;
			}
		}
	}
	while (botsType1.size() < 5)
	{
		botsType1.push_back(new Ai(60.0f, 30.0f, 15.0f, 1.0f, "21856_Koi_v1", "Resources/Textures/Fish/TropicalFish01.jpg"));
	}
	while (botsType2.size() < 5)
	{
		botsType2.push_back(new Ai(120.0f, 60.0f, 30.0f, 1.0f, "21856_Koi_v1", "Resources/Textures/Fish/TropicalFish02.jpg"));
	}
}

Game::~Game()
{
}
