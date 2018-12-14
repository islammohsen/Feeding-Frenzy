#include "ModelLoader.h"

map<string, Model> ModelLoader::Models;
vector<string> ModelLoader::modelNames;

void ModelLoader::ImportModels()
{
	modelNames = { "21856_Koi_v1" };
	for (string modelName : modelNames)
	{
		Models[modelName].m_data = OBJLoader::LoadObjModel(modelName);
		Models[modelName].m_rotation = OBJLoader::LoadObjRotation(modelName);
	}
}

Model ModelLoader::LoadModel(string name)
{
	return Models[name];
}