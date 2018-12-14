#include "Ai.h"
#include <time.h>
#include <chrono>
#include <random>

auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 mt_rand(seed);

Ai::Ai()
{
	fishCount = 10;
	fish = new Fish();
}

Ai* Ai::initialRandomPosition(string model, string texture)
{
	float xPos = (mt_rand() % 2048) - 1024.0f, yPos = (mt_rand() % 1440) - 720.0f, zPos = 512.0f, m_Xscale = 40.f, m_Yscale = 40.f, m_Zscale = 20.0f, m_speed = 1.0f;
	Ai* ret = new Ai();
	ret->currentXPos = xPos;
	ret->currentYPos = yPos;
	ret->fish = new Fish(xPos, yPos, zPos, m_Xscale, m_Yscale, m_Zscale, m_speed, model, texture);
	ret->speed = m_speed;
	setNextRandomPosition();
	return ret;
}

void Ai::setNextRandomPosition()
{
	this->nextXPos = (mt_rand() % 2048) - 1024.0f, this->nextYPos = (mt_rand() % 1440) - 720.0f;
}

void Ai::generateNextPoint()
{
	if (fabs(currentXPos - nextXPos) <= 10.0f && fabs(currentYPos - nextYPos) <= 10.0f)
	{
		setNextRandomPosition();
	}
}

void Ai::setFishCount(int fishCount)
{
	this->fishCount = fishCount;
}

int Ai::getFishCount()
{
	return this->fishCount;
}

void Ai::getGoing() 
{
	float slope = (nextYPos - currentYPos) / (nextXPos - currentXPos), oldx = currentXPos, oldy = currentYPos;
	if (currentXPos < nextXPos)
	{
		currentXPos += speed;
	} 
	else 
	{
		currentXPos -= speed;
	}
	currentYPos = nextYPos - slope * (nextXPos - currentXPos);
	//cout << currentXPos << ' ' << currentYPos << '\n';
	fish->move(currentXPos - oldx, currentYPos - oldy, 0.0f);
}

Ai::~Ai()
{
	delete fish;
}
