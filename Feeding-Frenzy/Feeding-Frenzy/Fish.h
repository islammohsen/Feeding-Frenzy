#ifndef FISH_H
#define FISH_H
#include "Texture.h"	 
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Renderer.h"
#include "OBJLoader.h"
#include <gL\glew.h>
#include <gl\glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "ModelLoader.h"

#include <chrono>
#include <random>
#include <time.h>

class Fish
{
protected:
	Model model;
	vector<unsigned int> index;
	vector<glm::vec3> collisionPolygon;
	VertexArray *m_vao;
	IndexBuffer *m_ibo;
	VertexBuffer *m_vbo;
	Texture *m_texture;
	float m_speed;
	int type;
	glm::mat4 m_translationMatrix;
	glm::mat4 m_scaleMatrix;
	glm::mat4 m_rotationMatrix;
private:
	void GetCollisionPoints();
public:
	Fish();
	Fish(float xPos, float yPos, float zPos, float m_Xscale, float m_Yscale, float m_Zscale, float m_speed, int type, string object, string texture);
	void Draw(Renderer *renderer, Shader* m_shader, glm::mat4 view, glm::mat4 projection);
	void move(float valx, float valy, float valz);
	void rotate(float angle, float x, float y, float z);
	void scale(float valx, float valy, float valz);
	void ResetRotation();
	int GetType();
	glm::vec3 GetPosition();
	glm::vec3 GetMouth();
	glm::vec3 GetLeftSide();
	glm::vec3 GetRightSide();
	vector<float> GetDimension(); //x min x max y min y max z min z max
	~Fish();
};
#endif



