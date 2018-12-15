#pragma once
#ifndef AI_H
#define AI_H
#include "Fish.h"

class Ai : public Fish
{
	int fishCount;
	float nextXPos;
	float nextYPos;
	float currentXPos;
	float currentYPos;
	float speed;
	float initialAngle;
public:
	
	Fish *fish;
	Ai();
	
	Ai* initialRandomPosition(string, string);
	void setNextRandomPosition();
	void generateNextPoint();
	void getGoing();
	void specificAttack(glm::vec2);
	bool pointInRange(glm::vec2, float);
	int getFishCount();
	void setFishCount(int);
	
	~Ai();
};
#endif
