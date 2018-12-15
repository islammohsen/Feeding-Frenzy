#pragma once
#ifndef AI_H
#define AI_H
#include "Fish.h"
#include <time.h>
#include <chrono>
#include <random>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Ai : public Fish
{
	float nextXPos;
	float nextYPos;
	float currentXPos;
	float currentYPos;
private:
	void getRotations();
	void setNextRandomPosition();
	void generateNextPoint();
public:
	Ai(float m_Xscale, float m_Yscale, float m_Zscale, float m_speed, string object, string texture);
	void getGoing();
	void specificAttack(glm::vec2);
	bool pointInRange(glm::vec2, float);
	~Ai();
};
#endif
