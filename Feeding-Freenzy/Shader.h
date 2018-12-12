#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

#include <gL\glew.h>
#include <gl\glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

using namespace std;

struct ShaderProgramSource
{
	string VertexSource;
	string FragmentSource;
};

class Shader
{
	std::string m_FilePath;
	unsigned int m_RendereID;
	unordered_map<string, int> m_UniformLocationCache;
public:
	Shader(const string& filepath);
	~Shader();
	void Bind() const;
	void Unbind() const;
	void setUniform1i(const string& uniformName, int value);
	void SetUniform4f(const string& uniformName, float f0, float f1, float f2, float f3);
	void SetUniformMat4f(const string& uniformName, glm::mat4 matrix);
private:
	ShaderProgramSource ParseShader(const string &filepath);
	unsigned int CompileShader(unsigned int type, const string& source);
	unsigned int createShader(const string& vertexShader, const string& fragmentShader);
	int GetUniformLocation(const string& uniformName);
};
