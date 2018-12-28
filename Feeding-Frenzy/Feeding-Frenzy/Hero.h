#pragma once
#ifndef HER0_H
#define HERO_H
#include "Fish.h"
#include "Camera.h"

enum Direction
{
	PostiveDirection, NegativeDirection
};

class Hero: public Fish
{
	float nextXPos;
	float nextYPos;
	float nextZPos;
	Direction direction;
	int score;
public:
	float currentXPos;
	float currentYPos;
	float currentZPos;
	float rotationAngle;
	Camera thirdPersonCamera;
	Camera firstPersonCamera;
	Hero(float xPos, float yPos, float zPos, float m_Xscale, float m_Yscale, float m_Zscale, float m_speed, int type, string object, string texture);
	void Eat();
	void move(float valx, float valy, float valz);
	void rotateTo(float angle);
	void rotate(float angle, float x, float y, float z);
	void scale(float valx, float valy, float valz);
	void updateFirstPersonCamera();
	void GoTo(float newNextXPos, float newNextYPos, float newNextZPos);
	void MoveForward();
	void getGoing();
	void getRotations();
	~Hero();
};
#endif
