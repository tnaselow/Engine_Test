#pragma once

#include "FPSCamera.h"

#define PI 3.14159265359f

FPSCamera::FPSCamera(Vector3 position, Vector3 up, float yaw, float pitch) : Front(Vector3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)
{
	this->Position = position;
	this->WorldUp = up;
	this->Yaw = yaw;
	this->Pitch = pitch;
	this->UpdateCameraVectors();
}


FPSCamera::FPSCamera(float posX, float posY, float posZ) : Front(Vector3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)
{
	this->Position = Vector3(posX, posY, posZ);
	this->WorldUp = Vector3(0.0f, 1.0f, 0.0f);
	this->Yaw = YAW;
	this->Pitch = PITCH;
	this->UpdateCameraVectors();
}

Matrix4 FPSCamera::GetViewMatrix()
{
	UpdateMatrix();
	return ViewMatrix;
}

void FPSCamera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = this->MovementSpeed * deltaTime;
	if (direction == FORWARD)
		this->Position += this->Front * velocity;
	if (direction == BACKWARD)
		this->Position -= this->Front * velocity;
	if (direction == LEFT)
		this->Position -= this->Right * velocity;
	//Right = Right * velocity;
	Right = Vector3(0, 1, 0);
	if (direction == RIGHT)
		this->Position += this->Right;
	
}

void FPSCamera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
	xoffset *= this->MouseSensitivity;
	yoffset *= this->MouseSensitivity;

	this->Yaw += xoffset;
	this->Pitch += yoffset;

	if (constrainPitch)
	{
		if (this->Pitch > 89.0f)
			this->Pitch = 89.0f;
		if (this->Pitch < -89.0f)
			this->Pitch = -89.0f;
	}

	UpdateCameraVectors();
}

void FPSCamera::ProcessMouseScroll(float yoffset)
{
	if (this->Zoom >= 1.0f && this->Zoom <= 45.0f)
		this->Zoom -= yoffset;
	if (this->Zoom <= 1.0f)
		this->Zoom = 1.0f;
	if (this->Zoom >= 45.0f)
		this->Zoom = 45.0f;
}

void FPSCamera::UpdateCameraVectors()
{
	Front.mX = cos(ToRadians(this->Yaw)) * cos(ToRadians(this->Pitch));
	Front.mY = sin(ToRadians(this->Pitch));
	Front.mZ = sin(ToRadians(this->Yaw)) * cos(ToRadians(this->Pitch));
	Front.Normalize();
	
	Right = WorldUp.Cross(Front).Normalize();
	Up = Front.Cross(Right).Normalize();	
}

float FPSCamera::ToRadians(float deg)
{
	return deg * (PI / 180.0f);
}

void FPSCamera::UpdateMatrix()
{
	Vector3 dir(Position);
	dir += Front;
	dir.Normalize();

	ViewMatrix.GetMatrixData()[0] = Right.mX;
	ViewMatrix.GetMatrixData()[1] = Right.mY;
	ViewMatrix.GetMatrixData()[2] = Right.mZ;
	ViewMatrix.GetMatrixData()[3] = -Position.mX;

	ViewMatrix.GetMatrixData()[4] = Up.mX;
	ViewMatrix.GetMatrixData()[5] = Up.mY;
	ViewMatrix.GetMatrixData()[6] = Up.mZ;
	ViewMatrix.GetMatrixData()[7] = -Position.mY;

	ViewMatrix.GetMatrixData()[8]  = dir.mX;
	ViewMatrix.GetMatrixData()[9]  = dir.mY;
	ViewMatrix.GetMatrixData()[10] = dir.mZ;
	ViewMatrix.GetMatrixData()[11] = -Position.mZ;
}