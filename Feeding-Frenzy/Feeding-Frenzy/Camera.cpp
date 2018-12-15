#include "Camera.h"



Camera::Camera(void)
{
	this->Reset(0, 0, 0,
		0, 0, -1,
		0, 1, 0);

	SetPerspectiveProjection(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
}


glm::vec3 Camera::GetLookDirection()
{
	return -mDirection;
}

void Camera::Reset(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ)
{
	glm::vec3 eyePt(eyeX, eyeY, eyeZ);
	glm::vec3 centerPt(centerX, centerY, centerZ);
	glm::vec3 upVec(upX, upY, upZ);
	Reset(eyePt, centerPt, upVec);
}

void Camera::Reset(const glm::vec3 &eye, const glm::vec3 &center, glm::vec3 &up)
{
	mPosition = eye;
	//still needs normalization
	mDirection = eye - center;
	//i = j x k
	mRight = glm::cross(up, mDirection);
	//j = k x i
	mUp = glm::cross(mDirection, mRight);
	//normalize all
	mUp = glm::normalize(mUp);
	mRight = glm::normalize(mRight);
	mDirection = glm::normalize(mDirection);
	UpdateViewMatrix();
}

glm::mat4 Camera::GetViewMatrix()
{
	return mViewMatrix;
}

void Camera::UpdateViewMatrix()
{
	glm::vec3 center = mPosition + this->GetLookDirection();
	mViewMatrix = glm::lookAt(mPosition, center, mUp);
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return mProjectionMatrix;
}

void Camera::SetPerspectiveProjection(float FOV, float aspectRatio, float near, float far)
{
	mProjectionMatrix = glm::perspective(FOV, aspectRatio, near, far);
}

void Camera::Slide(float stepR, float stepU, float stepD)
{
	mPosition += stepR *mRight;
	mPosition += stepU * mUp;
	//next transition needs to be tested!!.
	mPosition += stepD * mDirection;
}

void Camera::Yaw(float angleDegrees)
{
	// 2ldirection 2lle howa 2l z byt7rk m3a 2l 2tgah.

	mDirection = glm::rotate(mDirection, angleDegrees, mUp);
	mRight = glm::rotate(mRight, angleDegrees, mUp);
}

void Camera::Pitch(float angleDegrees)
{
	// 2ldirection 2lle howa 2l z byt7rk m3a 2l 2tgah.
	mUp = glm::rotate(mUp, angleDegrees, mRight);
	mDirection = glm::rotate(mDirection, angleDegrees, mRight);
	UpdateViewMatrix();
}

void Camera::Roll(float angleDegrees)
{
	// hna 3shan 7walen 2l Z hnlef 7waleh fa msh hyt7rk.

	// bm3na 2s7, kol vector btlef 7waleh, 2l 2 vectors 2ltanyen btlf 7walehom.
	mRight = glm::rotate(mRight, angleDegrees, mDirection);
	mUp = glm::rotate(mUp, angleDegrees, mDirection);
	UpdateViewMatrix();
}

void Camera::Walk(float dist)
{
	mPosition -= dist * mDirection; // bmshy 3ks 2ldirection 3shan 2l Z n7yty.
	UpdateViewMatrix();
}

void Camera::Strafe(float dist)
{
	mPosition += dist *mRight;
	UpdateViewMatrix();
}

void Camera::Fly(float dist)
{
	mPosition += dist * mUp;
	UpdateViewMatrix();
}









