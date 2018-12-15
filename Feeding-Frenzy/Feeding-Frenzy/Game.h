#pragma once
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
#include "ModelLoader.h"
#include "Ai.h"
#include "Hero.h"

class Game
{
	string textureShaderFileName = "Resources/shaders/TextureShader.shader";
	string basicShaderFileName = "Resources/shaders/Basic.shader";
	Level *level;
	Shader *basicShader, *textureShader;
	Renderer *renderer;
	vector<Ai*> botsType1, botsType2, botsType3;
	void Attack();
	float time;
public:
	Hero *ourHero;
	Game();
	void Initialize();
	void Draw();
	void Update();
	void CheckCollision();
	bool Collision(glm::vec2, vector<glm::vec2>);
	~Game();
	glm::mat4 view_matrix;
};

