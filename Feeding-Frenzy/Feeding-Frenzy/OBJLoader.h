#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

using namespace std;

static class OBJLoader
{
	static vector<string> split(string s, char delim);
	static void addVertex(vector<float> &Points, string s, vector<float> vertex, vector<float> texture, vector<float> normal);
	static void normalize(vector<float> &points);
	static void mult(float mat4[4][4], float vec[4]);
public:
	static vector<float> LoadObjModel(string FileName);
	static glm::mat4 LoadObjRotation(string FileName);
};

