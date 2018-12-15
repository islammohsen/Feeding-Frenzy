#include "Ai.h"

const float PI = acos(-1);

auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 mt_rand(seed);

Ai::Ai(float m_Xscale, float m_Yscale, float m_Zscale, float m_speed, string object, string texture):
	Fish(0.0f, 0.0f, 0.0f, m_Xscale, m_Yscale, m_Zscale, m_speed, object, texture)
{
	float xPos = (mt_rand() % 2048) - 1024.0f, yPos = (mt_rand() % 1440) - 720.0f, zPos = 512.0f;
	move(xPos, yPos, zPos);
	currentXPos = xPos;
	currentYPos = yPos;
	setNextRandomPosition();
}

void Ai::setNextRandomPosition()
{
	float newNextXPos, newNextYPos;
	do {
		newNextXPos = (mt_rand() % 2048) - 1024.0f, newNextYPos = (mt_rand() % 1440) - 720.0f;
	} while (fabs(newNextXPos - nextXPos) < 300.0f);
	nextXPos = newNextXPos;
	nextYPos = newNextYPos;
}

void Ai::generateNextPoint()
{
	if (fabs(currentXPos - nextXPos) <= 10.0f && fabs(currentYPos - nextYPos) <= 10.0f)
	{
		setNextRandomPosition();
	}
}

void Ai::specificAttack(glm::vec2 target)
{
	this->nextXPos = target.x;
	this->nextYPos = target.y;
}

bool Ai::pointInRange(glm::vec2 target, float distance)
{
	float currDist = (target.x - currentXPos) * (target.x - currentXPos) + (target.y - currentYPos) * (target.y - currentYPos);
	distance *= distance;
	return currDist <= distance;
}

void Ai::getGoing()
{
	generateNextPoint();
	float slope = (nextYPos - currentYPos) / (nextXPos - currentXPos), oldx = currentXPos, oldy = currentYPos;
	if (currentXPos < nextXPos)
	{
		currentXPos += m_speed;
	} 
	else 
	{
		currentXPos -= m_speed;
	}
	currentYPos = nextYPos - slope * (nextXPos - currentXPos);
	move(currentXPos - oldx, currentYPos - oldy, 0.0f);
	getRotations();
}

void Ai::getRotations()
{
	float currentRotation = (atan2(nextYPos - currentYPos, nextXPos - currentXPos) * 180.0f) / PI;
	if (fabs(currentRotation) > 90)
	{
		ResetRotation();
		rotate(180.0f, 0.0f, 1.0f, 0.0f);
		if (currentRotation > 0)
			rotate(180.0f - currentRotation, 0.0f, 0.0f, 1.0f);
		else
			rotate(fabs(currentRotation) - 180.0f, 0.0f, 0.0f, 1.0f);
	}
	if (fabs(currentRotation) < 90)
	{
		ResetRotation();
		rotate(currentRotation, 0.0f, 0.0f, 1.0f);
	}
}


Ai::~Ai()
{
}
