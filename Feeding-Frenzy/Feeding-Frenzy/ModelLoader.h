#pragma once
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "OBJLoader.h"

using namespace std;

class Model
{
public:
	vector<float> m_data;
	glm::mat4 m_rotation;
	Model()
	{
		m_rotation = glm::mat4(1);
	}
};

static class ModelLoader
{
	static map<string, Model> Models;
	static vector<string> modelNames;
public:
	static void ImportModels();
	static Model LoadModel(string name);
};

