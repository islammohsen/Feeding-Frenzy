#include "Shader.h"
#include "Renderer.h"

Shader::Shader(const std::string& filepath)
{
	this->m_FilePath = filepath;
	this->m_RendereID = 0;
	ShaderProgramSource shaderSource = ParseShader(filepath);
	m_RendereID = createShader(shaderSource.VertexSource, shaderSource.FragmentSource);
}

ShaderProgramSource Shader::ParseShader(const string &filepath)
{
	ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	string line;
	stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != string::npos)
		{
			if (line.find("vertex") != string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			if (type == ShaderType::NONE)
				continue;
			ss[(int)type] << line << '\n';
		}
	}
	ShaderProgramSource Shaders;
	Shaders.VertexSource = ss[0].str();
	Shaders.FragmentSource = ss[1].str();
	return Shaders;
}

unsigned int Shader::CompileShader(unsigned int type, const string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		cout << "failed to compile shader!\n";
		cout << message << '\n';
		GLCall(glDeleteShader(id));
		return 0;
	}
	return id;
}

unsigned int Shader::createShader(const string& vertexShader, const string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}


void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendereID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::setUniform1i(const string & uniformName, int value)
{
	int location = GetUniformLocation(uniformName);
	GLCall(glUniform1i(location, value));
}

void Shader::SetUniform4f(const std::string& uniformName, float f0, float f1, float f2, float f3)
{
	int location = GetUniformLocation(uniformName);
	GLCall(glUniform4f(location, f0, f1, f2, f3));
}

void Shader::SetUniformMat4f(const string & uniformName, glm::mat4 matrix)
{
	int location = GetUniformLocation(uniformName);
	GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string & uniformName)
{
	if (m_UniformLocationCache.find(uniformName) != m_UniformLocationCache.end())
		return m_UniformLocationCache[uniformName];
	GLCall(int location = glGetUniformLocation(m_RendereID, uniformName.c_str()))
	return m_UniformLocationCache[uniformName] = location;
}

Shader::~Shader()
{
	glDeleteProgram(m_RendereID);
}
