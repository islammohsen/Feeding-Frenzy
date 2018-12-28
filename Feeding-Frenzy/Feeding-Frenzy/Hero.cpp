#include "Hero.h"
/*
auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 mt_rand(seed);
*/
const float PI = acos(-1);
#define EPS 10

Hero::Hero(float xPos, float yPos, float zPos, float m_Xscale, float m_Yscale, float m_Zscale, float m_speed, int type, string object, string texture) :Fish(xPos, yPos, zPos, m_Xscale, m_Yscale, m_Zscale, m_speed, type, object, texture)
{
	score = 0;
	thirdPersonCamera.SetPerspectiveProjection(45.0f, 1024.0f / 720.0f, 0.1f, 10000.0f);
	currentXPos = nextXPos = xPos;
	currentYPos = nextYPos = yPos;
	currentZPos = nextZPos = zPos;
	thirdPersonCamera.Strafe(xPos);
	thirdPersonCamera.Fly(yPos);
	thirdPersonCamera.Walk(-2000.0f);
	firstPersonCamera.SetPerspectiveProjection(45.0f, 1024.0f / 720.0f, 0.1f, 10000.0f);
	updateFirstPersonCamera();
	direction = PostiveDirection;
}

void Hero::Eat()
{
	score++;
	if (score <= 10 && score % 5 == 0) {
		type++;
		scale(2.0f, 2.0f, 2.0f);
	}
}

void Hero::move(float valx, float valy, float valz)
{
	thirdPersonCamera.Strafe(valx);
	thirdPersonCamera.Fly(valy);
	m_translationMatrix = glm::translate(m_translationMatrix, glm::vec3(valx, valy, valz));
	updateFirstPersonCamera();
}

void Hero::rotateTo(float angle)
{
	rotationAngle = angle;
	cout << rotationAngle << ' ' << angle << '\n';
	while (rotationAngle > 360)
	{
		rotationAngle -= 360;
		cout << "1 " << rotationAngle << '\n';
	}
	while (rotationAngle < 0)
	{
		rotationAngle += 360;
		cout << "2 " << rotationAngle << '\n';
	}
	if (rotationAngle > 90.0f && rotationAngle < 270.0f) {
		ResetRotation();
		rotate(180.0f, 0.0f, 1.0f, 0.0f);
		rotate(180.0f - rotationAngle, 0.0f, 0.0f, 1.0f);
	}
	else
	{
		ResetRotation();
		if (rotationAngle < 90.0f)
			rotate(rotationAngle, 0.0f, 0.0f, 1.0f);
		else
			rotate(rotationAngle - 360.0f, 0.0f, 0.0f, 1.0f);
	}
	updateFirstPersonCamera();
}

void Hero::rotate(float angle, float x, float y, float z)
{
	m_rotationMatrix *= glm::rotate(angle, glm::vec3(x, y, z));
}

void Hero::scale(float valx, float valy, float valz)
{
	m_scaleMatrix = glm::scale(m_scaleMatrix, glm::vec3(valx, valy, valz));
	updateFirstPersonCamera();
}

void Hero::MoveZ(float val)
{
	glm::vec3 left = GetLeftSide();
	glm::vec3 right = GetRightSide();
	left.z += val, right.z += val;
	if (left.z >= 1024.0f || left.z <= 0 || right.z >= 1024.0f || right.z <= 0)
		return;
	currentZPos += val;
	move(0, 0, val);
}

void Hero::updateFirstPersonCamera()
{
	glm::vec3 eye = GetMouth();
	glm::vec3 test = GetPosition();
	glm::vec4 center = glm::vec4(GetPosition(), 1.0f);

	float slope;
	if (fabs(eye.x - center.x) < 1e-9)
	{
		if (center.y < eye.y)
			center.y += 1024.0f;
		else
			center.y -= 1024.0f;
	}
	else
	{
		slope = (eye.y - center.y) / (eye.x - center.x);
		if (eye.x > center.x)
			center.x += 1024.0f, center.y += 1024.0f * slope;
		else
			center.x += -1024.0f, center.y += -1024.0f * slope;
	}
	//center = m_rotationMatrix * center;
	firstPersonCamera.Reset(eye.x, eye.y, eye.z, center.x, center.y, center.z, 0.0f, 1.0f, 0.0f);
}

void Hero::GoTo(float newNextXPos, float newNextYPos)
{
	nextXPos = newNextXPos;
	nextYPos = newNextYPos;
}

void Hero::MoveForward(float val)
{
	glm::vec3 center = GetPosition();
	glm::vec3 mouth = GetMouth();

	float slope;
	if (fabs(mouth.x - center.x) < 1e-9)
	{
		if (center.y < mouth.y)
			GoTo(currentXPos, currentYPos + val);
		else
			GoTo(currentXPos, currentYPos - val);
	}
	else 
	{
		slope = (mouth.y - center.y) / (mouth.x - center.x);
		if (mouth.x > center.x)
			GoTo(currentXPos + val, currentYPos + val * slope);
		else
			GoTo(currentXPos - val, currentYPos - val * slope);
	}
}


void Hero::getGoing()
{
	glm::vec3 mouth = GetMouth();
	float  oldx = currentXPos, oldy = currentYPos, oldz = currentZPos;
	float slope1, slope2;
	
	if (fabs(currentXPos - nextXPos) < EPS)
		return;

	slope1 = (nextYPos - currentYPos) / (nextXPos - currentXPos), slope2 = (nextZPos - currentZPos) / (nextXPos - currentXPos);

	currentXPos += m_speed * (currentXPos < nextXPos ? 1 : -1);
	mouth.x += m_speed * (currentXPos < nextXPos ? 1 : -1);

	currentYPos += m_speed * slope1 * (currentXPos < nextXPos ? 1 : -1);
	mouth.y += m_speed * slope1 * (currentXPos < nextXPos ? 1 : -1);

	if (mouth.x >= 1024.0f || mouth.x <= -1024.0f || mouth.y >= 720.0f || mouth.y <= -720.0f)
	{
		currentXPos = oldx;
		currentYPos = oldy;
		currentZPos = oldz;
		return;
	}
	move(currentXPos - oldx, currentYPos - oldy, currentZPos - oldz);
	getRotations();
}

void Hero::getRotations()
{
	float currentRotation = (atan2(nextYPos - currentYPos, nextXPos - currentXPos) * 180.0f) / PI;
	rotateTo(currentRotation);
}

Hero::~Hero()
{
}
