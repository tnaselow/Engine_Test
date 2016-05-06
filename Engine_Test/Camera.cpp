#include "Camera.h"

#define PI 3.14159265359f


namespace
{
	Vector3 WorldUp(0, 1.0f, 0);

	float ToRadians(float deg)
	{
		return deg * (PI / 180.0f);
	}
}

Camera::Camera(const Vector3  &pos) : mForward(0, 0, -1), mRight(1, 0, 0)
{
	mPosition = pos;

	mPitch = 0.0f;
	mYaw = 0.0f;
	mRoll = 0.0f;
	mZoom = 0.0f;
}

Camera::Camera(float x, float y, float z) : mForward(0, 0, -1), mRight(1, 0, 0)
{
	mPosition.X = x;
	mPosition.Y = y;
	mPosition.Z = z;

	mPitch = 0.0f;
	mYaw = 0.0f;
	mRoll = 0.0f;
	mZoom = 0.0f;
}

void Camera::SetPosition(const Vector3 &vec)
{
	mPosition = vec;
}

void Camera::SetPosition(float x, float y, float z)
{
	mPosition.X = x;
	mPosition.Y = y;
	mPosition.Z = z;
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = 3.0f * deltaTime;
	if (direction == FORWARD)
		this->mPosition += this->mForward * velocity;
	if (direction == BACKWARD)
		this->mPosition -= this->mForward * velocity;
	if (direction == LEFT)
		this->mPosition -= this->mRight * velocity;
	if (direction == RIGHT)
		this->mPosition += this->mRight * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset)
{
	xoffset *= 0.05f;
	yoffset *= 0.05f;

	this->mYaw -= xoffset;
	this->mPitch += yoffset;

	if (this->mPitch > 89.0f)
		this->mPitch = 89.0f;
	if (this->mPitch < -89.0f)
		this->mPitch = -89.0f;

	mForward.X = cos(ToRadians(mPitch - 180.0f)) * sin(ToRadians(mYaw));
	mForward.Y = sin(ToRadians(mPitch));
	mForward.Z = cos(ToRadians(mPitch - 180.0f)) * cos(ToRadians(mYaw));
	mForward.Normalize();
	mRight = mForward.Cross(WorldUp);
	mRight.Normalize();
}

float Camera::ProcessMouseScroll(float yoffset)
{
	if (this->mZoom >= 1.0f && this->mZoom <= 45.0f)
		this->mZoom -= yoffset;
	if (this->mZoom <= 1.0f)
		this->mZoom = 1.0f;
	if (this->mZoom >= 45.0f)
		this->mZoom = 45.0f;
	return mZoom;
}



void Camera::SetViewMatrix()
{
	mViewMatrix.SetToIdentity();

	mViewMatrix.RotateDeg(mPitch, ROT_AXIS::X_AXIS);
	mViewMatrix.RotateDeg(mYaw, ROT_AXIS::Y_AXIS);
	mViewMatrix.RotateDeg(mRoll, ROT_AXIS::Z_AXIS);
	mViewMatrix.Translate(mPosition);
}

Matrix4 Camera::GetViewMatrix()
{
	SetViewMatrix();
	return mViewMatrix.GetInverse();
}

Vector3 &Camera::GetPosition()
{
	return mPosition;
}