#pragma once

#include "FPSCamera.h"
#include <iostream>

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
	if (direction == RIGHT)
		this->Position += this->Right * velocity;

	std::cout << ViewMatrix << std::endl;
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
	Front.X = cos(ToRadians(this->Yaw)) * cos(ToRadians(this->Pitch));
	Front.Y = sin(ToRadians(this->Pitch));
	Front.Z = sin(ToRadians(this->Yaw)) * cos(ToRadians(this->Pitch));
	Front.Normalize();

	Right = Front.Cross(WorldUp).Normalize();
	Up = Right.Cross(Front).Normalize();
}

float FPSCamera::ToRadians(float deg)
{
	return deg * (PI / 180.0f);
}

void FPSCamera::UpdateMatrix()
{
	Vector3 dir;
	dir = (Position + Front) - Position;
	dir.Normalize();

	ViewMatrix.GetMatrixData()[0] = Right.X;
	ViewMatrix.GetMatrixData()[1] = Right.Y;
	ViewMatrix.GetMatrixData()[2] = Right.Z;
	ViewMatrix.GetMatrixData()[3] = -Position.X;

	ViewMatrix.GetMatrixData()[4] = Up.X;
	ViewMatrix.GetMatrixData()[5] = Up.Y;
	ViewMatrix.GetMatrixData()[6] = Up.Z;
	ViewMatrix.GetMatrixData()[7] = -Position.Y;

	ViewMatrix.GetMatrixData()[8]  = dir.X;
	ViewMatrix.GetMatrixData()[9]  = dir.Y;
	ViewMatrix.GetMatrixData()[10] = dir.Z;
	ViewMatrix.GetMatrixData()[11] = -Position.Z;
}