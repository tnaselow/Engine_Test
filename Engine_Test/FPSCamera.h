#pragma once

#include <vector>
#include "Sapph\Matrix4.h"
#include "Sapph\Vector3.h"

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

namespace
{
	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float SPEED = 3.0f;
	const float SENSITIVTY = 0.25f;
	const float ZOOM = 45.0f;
}

class FPSCamera
{
public:
	Vector3 Position;
	Vector3 Front;
	Vector3 Up;
	Vector3 Right;
	Vector3 WorldUp;
	Matrix4 ViewMatrix;

	float Yaw;
	float Pitch;
	
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	FPSCamera(Vector3 position = Vector3(0.0f, 0.0f, 0.0f), Vector3 up = Vector3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	FPSCamera(float posX, float posY, float posZ);
	
	Matrix4 GetViewMatrix();
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);

	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

	void ProcessMouseScroll(float yoffset);
	void UpdateCameraVectors();
	void UpdateMatrix();
private:
	
	float ToRadians(float deg);
};