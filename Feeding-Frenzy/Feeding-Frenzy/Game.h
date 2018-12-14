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

class Game
{
	string textureShaderFileName = "Resources/shaders/TextureShader.shader";
	string basicShaderFileName = "Resources/shaders/Basic.shader";
	vector<Fish*> Fishes;
	Level *level;
	Shader *basicShader, *textureShader;
	Renderer *renderer;
public:
	Game();
	void Initialize();
	void Draw();
	~Game();
	glm::mat4 view_matrix;
};

