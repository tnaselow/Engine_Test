#pragma once
#include "Vector3.h"
#include <iostream>

enum ROT_AXIS
{
	X_AXIS,
	Y_AXIS,
	Z_AXIS
};

class Matrix4
{
	public:

		static const int Width = 4;
		Matrix4();
		Matrix4(const Matrix4 &mat);
		~Matrix4();


		Vector3 operator *(const Vector3 &vec) const;
		Matrix4 operator *(const Matrix4 &mat) const;
		Matrix4 operator *(float scalar) const;
		Matrix4 &operator *=(const Matrix4 &mat);
		Matrix4 &operator *=(float scalar);
		Matrix4 &operator=(const Matrix4 &mat);
		bool operator==(const Matrix4 &mat) const;

		Matrix4 GetTranspose();
		Matrix4 GetInverse();

		
		Matrix4 &Scale(float scalar); //
		Matrix4 &Translate(float x, float y, float z); 
		Matrix4 &Translate(const Vector3 &vec);
		Matrix4 &SetRotationDeg(float deg, ROT_AXIS axis = ROT_AXIS::Z_AXIS); 
		Matrix4 &SetRotationRad(float rad, ROT_AXIS axis = ROT_AXIS::Z_AXIS);

		Matrix4 &RotateDeg(float deg, ROT_AXIS axis = ROT_AXIS::Z_AXIS);
		Matrix4 &RotateRad(float deg, ROT_AXIS axis = ROT_AXIS::Z_AXIS);

		Matrix4 &SetToTranspose();
		bool SetToInverse();
		Matrix4 &SetToIdentity();

		Vector3 MultiplyVec(const Vector3 &vec, float w = 0);

		float *GetMatrixData();
		float GetCell(int x, int y);

		void SetOrtho(float left, float right, float bottom, float top, float near, float far);
		void SetPerspective(float fov, float aspectRatio, float nearPlane, float farPlane);

		friend std::ostream &operator<<(std::ostream &os, const Matrix4 &mat);

	private:
		float mMatrix[16];
};