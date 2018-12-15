#pragma once
#include "Fish.h"
#include "Camera.h"

class Hero: public Fish
{
	float nextXPos;
	float nextYPos;
	int score;
public:
	float currentXPos;
	float currentYPos;
	Camera playerCamera;
	Hero(float xPos, float yPos, float zPos, float m_Xscale, float m_Yscale, float m_Zscale, float m_speed, string object, string texture);
	void Eat();
	void move(float valx, float valy, float valz);
	void scale(float valx, float valy, float valz);
	void GoTo(float newNextXPos, float newNextYPos);
	void getGoing();
	void getRotations();
	~Hero();
};

