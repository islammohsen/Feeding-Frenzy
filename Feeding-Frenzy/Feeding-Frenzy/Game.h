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

class Game
{
	string textureShaderFileName = "Resources/shaders/TextureShader.shader";
	string basicShaderFileName = "Resources/shaders/Basic.shader";
	vector<Fish*> Fishes;
	Level *level;
	Shader *basicShader, *textureShader;
	Renderer *renderer;
	Ai mainBot;
	vector<Ai*> bots;
public:
	Game();
	void Initialize();
	void Draw();
	bool Collision(vector<glm::vec2>, glm::vec2, vector<glm::vec2>);
	~Game();
	glm::mat4 view_matrix;
};

