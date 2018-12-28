#include "OBJLoader.h"
#include <sstream>
#include <string>
using namespace std;

vector<float> OBJLoader::LoadObjModel(string FileName)
{
	vector<float> Points;
	vector<float> vertex, texture, normal;
	fstream fs("Resources/objects/" + FileName + ".obj", std::fstream::in | std::fstream::out);
	char temp[256];
	bool face = 0;
	while (fs.getline(temp, 256))
	{
		string line;
		for (int i = 0; i < temp[i]; i++)
		{
			line += temp[i];
		}
		if (line.empty())
			continue;
		vector<string> currentLine = split(line, ' ');
		if (currentLine[0] == "v")
		{
			stringstream ss;
			ss << currentLine[1];
			ss << ' ';
			ss << currentLine[2];
			ss << ' ';
			ss << currentLine[3];
			float x, y, z;
			ss >> x >> y >> z;
			vertex.push_back(x);
			vertex.push_back(y);
			vertex.push_back(z);
		}
		else if (currentLine[0] == "vt")
		{
			stringstream ss;
			ss << currentLine[1];
			ss << ' ';
			ss << currentLine[2];
			float x, y;
			texture.push_back(x);
			texture.push_back(y);
		}
		else if (currentLine[0] == "vn")
		{
			stringstream ss;
			ss << currentLine[1];
			ss << ' ';
			ss << currentLine[2];
			ss << ' ';
			ss << currentLine[3];
			float x, y, z;
			normal.push_back(x);
			normal.push_back(y);
			normal.push_back(z);
		}
	}
	fs.close();
	normalize(vertex);
	fs.open("Resources/objects/" + FileName + ".obj", std::fstream::in | std::fstream::out);
	while (fs.getline(temp, 256))
	{
		string line;
		for (int i = 0; i < 256; i++)
		{
			if (temp[i] == 0)
				break;
			line += temp[i];
		}
		if (line.empty())
			continue;
		vector<string> currentLine = split(line, ' ');
		if (currentLine[0] == "f")
		{
			if (currentLine.size() == 4) {
				addVertex(Points, currentLine[1], vertex, texture, normal);
				addVertex(Points, currentLine[2], vertex, texture, normal);
				addVertex(Points, currentLine[3], vertex, texture, normal);
			}
			else
			{
				//first face
				addVertex(Points, currentLine[1], vertex, texture, normal);
				addVertex(Points, currentLine[2], vertex, texture, normal);
				addVertex(Points, currentLine[3], vertex, texture, normal);
				//second face
				addVertex(Points, currentLine[2], vertex, texture, normal);
				addVertex(Points, currentLine[3], vertex, texture, normal);
				addVertex(Points, currentLine[1], vertex, texture, normal);
			}
		}
	}
	return Points;
	
}

glm::mat4 OBJLoader::LoadObjRotation(string FileName)
{
	fstream fs("Resources/Rotations/" + FileName + ".txt", std::fstream::in | std::fstream::out);
	char temp[256];
	glm::mat4 ret = glm::mat4(1);
	while (fs.getline(temp, 256))
	{
		string line;
		for (int i = 0; i < 256; i++)
		{
			if (temp[i] == 0)
				break;
			line += temp[i];
		}
		vector<string> currentLine = split(line, ' ');
		float angle, x, y, z;
		stringstream ss;
		ss << currentLine[0] << ' ' << currentLine[1] << ' ' << currentLine[2] << ' ' << currentLine[3];
		ss >> angle >> x >> y >> z;
		ret = glm::rotate(ret, angle, glm::vec3(x, y, z));
	}
	return ret;
}

void OBJLoader::addVertex(vector<float> &Points, string s, vector<float> vertex, vector<float> texture, vector<float> normal)
{
	vector<string> face = split(s, '/');
	int vertexIndex, textureIndex, normalIndex;
	stringstream ss;
	ss << face[0] << ' ' << face[1] << ' ' << face[2];
	ss >> vertexIndex >> textureIndex >> normalIndex;
	vertexIndex--;
	textureIndex--;
	normalIndex--;
	for(int i = 0; i < 3; i++)
		Points.push_back(vertex[vertexIndex * 3 + i]);
	for(int i = 0; i < 2; i++)
		Points.push_back(texture[textureIndex * 2 + i]);
	for (int i = 0; i < 3; i++)
		Points.push_back(normal[normalIndex * 3 + i]);
}

void OBJLoader::normalize(vector<float>& points)
{
	float xMin = 1e18, xMax = -1e18, yMin = 1e18, yMax = -1e18, zMin = 1e18, zMax = -1e18;
	for (int i = 0; i < points.size(); i += 3)
	{
		xMin = min(xMin, points[i]);
		xMax = max(xMax, points[i]);
		yMin = min(yMin, points[i + 1]);
		yMax = max(yMax, points[i + 1]);
		zMin = min(zMin, points[i + 2]);
		zMax = max(zMax, points[i + 2]);
	}
	float mat4[4][4] = { {2.0f / (xMax - xMin), 0.0f, 0.0f, - ((xMax + xMin) / (xMax - xMin))}, 
	{ 0.0f, 2.0f / (yMax - yMin), 0.0f, -((yMax + yMin) / (yMax - yMin)) },
	{ 0.0f, 0.0f, 2.0f / (zMax - zMin), -((zMax + zMin) / (zMax - zMin)) },
	{0, 0, 0, 0} };
	for (int i = 0; i < points.size(); i += 3) {
		float vec[4] = { points[i], points[i + 1], points[i + 2], 1 };
		mult(mat4, vec);
		for (int j = 0; j < 3; j++)
			points[i + j] = vec[j];
	}

}

void OBJLoader::mult(float mat4[4][4], float vec[4])
{
	float temp[4];
	for (int i = 0; i < 4; i++)
	{
		temp[i] = 0;
		for (int j = 0; j < 4; j++)
			temp[i] += mat4[i][j] * vec[j];
	}
	for (int i = 0; i < 4; i++)
		vec[i] = temp[i];
}

vector<string> OBJLoader::split(string s, char delim)
{
	vector<string> ret;
	string cur;
	for (char c: s)
	{
		if (c == delim)
		{
			if (cur != "")
				ret.push_back(cur);
			cur = "";
		}
		else
			cur += c;
	}
	if (cur != "")
		ret.push_back(cur);
	return ret;
}