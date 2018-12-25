#pragma once
#ifndef AI_H
#define AI_H
#include "Fish.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Ai : public Fish
{
	float nextXPos;
	float nextYPos;
	float nextZPos;
	float currentXPos;
	float currentYPos;
	float currentZPos;
private:
	void getRotations();
	void setNextRandomPosition();
	void generateNextPoint();
public:
	Ai(float m_Xscale, float m_Yscale, float m_Zscale, float m_speed, int type, string object, string texture);
	void getGoing();
	void specificAttack(glm::vec3);
	bool pointInRange(glm::vec3, float);
	~Ai();
};
#endif
