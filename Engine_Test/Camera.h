#pragma once

#include "Sapph\Vector3.h"
#include "Sapph\Matrix4.h"

enum Camera_Movement 
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
	public:
		Camera(const Vector3  &pos);
		Camera(float x = 0.0f, float y = 0.0f, float z = 0.0f);


		void SetPosition(const Vector3 &vec);
		void SetPosition(float x, float y, float z);

		void ProcessKeyboard(Camera_Movement direction, float deltaTime);
		void ProcessMouseMovement(float xoffset, float yoffset);
		float ProcessMouseScroll(float yoffset);
		
		void SetViewMatrix();
		Matrix4 GetViewMatrix();

		Vector3 &GetPosition();

	private:
		Matrix4 mViewMatrix;
		Vector3 mPosition;
		Vector3 mForward;
		Vector3 mRight;

		float mPitch;
		float mYaw;
		float mRoll;

		float mZoom;
};