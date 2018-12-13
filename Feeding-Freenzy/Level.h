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
	vector<float> BackgroundPoints;
	vector<unsigned int> Backgroundindex;
	VertexArray *m_vao;
	IndexBuffer *m_ibo;
	VertexBuffer *m_vbo;
	vector<Texture*> m_texture;
	float x_scale;
	float y_scale;
	float z_scale;
	glm::mat4 m_model;
	glm::mat4 m_translationMatrix;
	glm::mat4 m_scaleMatrix;
	glm::mat4 m_rotationMatrix;
	
public:
	Background(float x, float y, float z, float x_scale, float y_scale, float z_scale, vector<string> texture);
	void Draw(Renderer *renderer, Shader* m_shader, glm::mat4 view, glm::mat4 projection);
	void move(float valx, float valy, float valz);
	void rotate(float angle, float x, float y, float z);
	void scale(float valx, float valy, float valz);
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

