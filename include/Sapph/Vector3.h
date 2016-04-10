#pragma once
#include <iostream>

class Vector3
{
	public:
		Vector3(float x = 0, float y = 0, float z = 0);
		Vector3(const Vector3 &vec);
		~Vector3();

		void Set(float x, float y, float z);

		float Dot(const Vector3 &vec) const;
		float Magnitude() const;
		Vector3 Cross(const Vector3 &vec) const;
		Vector3 &Scale(float scalar);
		Vector3 &Normalize();

		Vector3 &operator=(const Vector3 &vec);
		bool operator==(const Vector3 &vec);

		Vector3 &operator /=(float scalar);
		Vector3 &operator *=(float scalar);
		Vector3 &operator +=(const Vector3 &vec);
		Vector3 &operator -=(const Vector3 &vec);

		Vector3 operator /(float scalar) const;
		Vector3 operator *(float scalar) const;
		Vector3 operator +(const Vector3 &vec) const;
		Vector3 operator -(const Vector3 &vec) const;

		friend std::ostream &operator<<(std::ostream &os, const Vector3 &vec);

		float X, Y, Z;
};