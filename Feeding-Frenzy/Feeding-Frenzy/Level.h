#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Renderer.h"
#include <gL\glew.h>
#include <gl\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Boarder 
{
	VertexArray *m_vao;
	IndexBuffer *m_ibo;
	VertexBuffer *m_vbo;
public:
	Boarder(void *data, unsigned int size, unsigned int *indexData, unsigned int count);
	void Draw(Renderer *renderer, Shader* m_shader, glm::mat4 view, glm::mat4 projection);
};
class Background
{
	VertexArray *m_vao;
	IndexBuffer *m_ibo;
	VertexBuffer *m_vbo;
	Texture *m_texture;
public:
	Background(string texture);
	void Draw(Renderer *renderer, Shader* m_shader, glm::mat4 view, glm::mat4 projection);
};

class Level
{
	Background *background;
	Boarder *boarder;
public:
	Level(int levelNumber);
	~Level();
	void DrawBackground(Renderer * renderer, Shader * m_shader, glm::mat4 view, glm::mat4 projection);
	void DrawBoarder(Renderer * renderer, Shader * m_shader, glm::mat4 view, glm::mat4 projection);
};

