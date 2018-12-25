#pragma once
#ifndef HER0_H
#define HERO_H
#include "Fish.h"
#include "Camera.h"

class Hero: public Fish
{
	float nextXPos;
	float nextYPos;
	float nextZPos;
	int score;
public:
	float currentXPos;
	float currentYPos;
	float currentZPos;
	Camera playerCamera;
	Hero(float xPos, float yPos, float zPos, float m_Xscale, float m_Yscale, float m_Zscale, float m_speed, int type, string object, string texture);
	void Eat();
	void move(float valx, float valy, float valz);
	void GoTo(float newNextXPos, float newNextYPos, float newNextZPos);
	void getGoing();
	void getRotations();
	~Hero();
};
#endif
