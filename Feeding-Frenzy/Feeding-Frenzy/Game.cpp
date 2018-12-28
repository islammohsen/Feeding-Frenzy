#include "Game.h"
#include "Hero.h"

void Game::Attack()
{
	
}

Game::Game()
{
}


typedef struct {
	double x, y, z;
} XYZ;
#define EPSILON  0.0000001
#define MODULUS(p) (sqrt(p.x*p.x + p.y*p.y + p.z*p.z))
#define TWOPI 6.283185307179586476925287
#define RTOD 57.2957795

//double CalcAngleSum(XYZ q, XYZ *p, int n)
bool PointInPolygon(const vector<glm::vec3> &p, glm::vec3 q)
{
	int i, n = p.size();
	double m1, m2;
	double anglesum = 0, costheta;
	XYZ p1, p2;

	for (i = 0; i < n; i++) {

		p1.x = p[i].x - q.x;
		p1.y = p[i].y - q.y;
		p1.z = p[i].z - q.z;
		p2.x = p[(i + 1) % n].x - q.x;
		p2.y = p[(i + 1) % n].y - q.y;
		p2.z = p[(i + 1) % n].z - q.z;

		m1 = MODULUS(p1);
		m2 = MODULUS(p2);
		if (m1*m2 <= EPSILON)
			return(TWOPI); /* We are on a node, consider this inside */
		else
			costheta = (p1.x*p2.x + p1.y*p2.y + p1.z*p2.z) / (m1*m2);

		anglesum += acos(costheta);
	}
	return fabs(anglesum - 1e-9) <= 360.0f;
}

/*bool PointInPolygon(const vector<glm::vec3> &p, glm::vec3 q) {
	bool c = 0;
	for (int i = 0; i < p.size(); i++) {
		int j = (i + 1) % p.size();
		if ((p[i].y <= q.y && q.y < p[j].y ||
			p[j].y <= q.y && q.y < p[i].y) &&
			q.x < p[i].x + (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y))
			c = !c;
	}
	return c;
}*/


bool Game::Collision(glm::vec3 mouth, vector<glm::vec3> target)
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
	mode = ThirdPerson;
	level = new Level(0);
	view_matrix = glm::lookAt(
		glm::vec3(0.0f, 0.0f, 720.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
	ourHero = new Hero(0.0f, 0.0f, 512.0f, 120.0f, 40.0f, 30.0f, 3.0f, 2, "3d-model", "Resources/Textures/Fish/TropicalFish10.jpg");
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

	glm::mat4 proj;
	glm::mat4 view;

	if (mode == ThirdPerson)
	{
		proj = ourHero->thirdPersonCamera.GetProjectionMatrix();
		view = ourHero->thirdPersonCamera.GetViewMatrix();
	}
	if (mode == FirstPerson) {
		proj = ourHero->firstPersonCamera.GetProjectionMatrix();
		view = ourHero->firstPersonCamera.GetViewMatrix();
	}
	level->DrawBackground(renderer, textureShader, view, proj);
	ourHero->Draw(renderer, textureShader, view, proj);
	for (auto &currentBot : bots)
		currentBot->Draw(renderer, textureShader, view, proj);
}

void Game::Update()
{
	float newTime = glfwGetTime();

	if (newTime - time >= 2) {
		//cout << "attack triggered\n";
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
		glm::vec3 mouth = bots[i]->GetMouth();
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
