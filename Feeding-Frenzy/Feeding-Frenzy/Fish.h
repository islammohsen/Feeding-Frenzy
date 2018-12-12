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

class Fish  
{
	vector<float> points;
	vector<unsigned int> index;
	VertexArray *m_vao;
	IndexBuffer *m_ibo;
	VertexBuffer *m_vbo;
	Texture *m_texture;
	float m_scale;
	float m_speed;
	glm::mat4 m_translationMatrix;
	glm::mat4 m_scaleMatrix;
	glm::mat4 m_rotationMatrix;
public:
	Fish(float xPos, float yPos, float zPos, float m_Xscale, float m_Yscale, float m_Zscale, float m_speed, string texture);
	void Draw(Renderer *renderer, Shader* m_shader, glm::mat4 view, glm::mat4 projection);
	void move(float valx, float valy, float valz);
	void rotate(float angle, float x, float y, float z);
	void scale(float valx, float valy, float valz);
	~Fish();
};

