#include "Renderer.h"
#include <iostream>

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char *file, int line)
{
	bool ret = true;
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " << function << ' ' << file << ": " << line << '\n';
		ret = false;
	}
	return ret;
}

Renderer::Renderer()
{
}

void Renderer::Clear() const
{
	GLCall(glClearColor(1.0f, 1.0f, 1.0f, 0.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::Draw(VertexArray * va, IndexBuffer * ib, Shader * shader, GLenum mode) const
{
	shader->Bind();
	va->Bind();
	ib->Bind();
	
	GLCall(glDrawElements(mode, ib->GetCount(), GL_UNSIGNED_INT, NULL));
}

