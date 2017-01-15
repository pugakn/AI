#pragma once
#include <iostream>

using namespace std;

struct VECTOR3D
{
public:
	union
	{
		struct
		{
			float x, y, z;
		};
		struct
		{
			float r, g, b;
		};
		struct
		{
			long lx, ly, lz;
		};
		float v[3];

	};
	VECTOR3D();
	VECTOR3D(const VECTOR3D& V);
	VECTOR3D(float fx, float fy, float fz);
	~VECTOR3D();
};

ostream& operator << (ostream& out, const VECTOR3D& V);
istream& operator >> (istream& in, VECTOR3D& V);
VECTOR3D operator* (const VECTOR3D &A, const VECTOR3D &B);
VECTOR3D operator* (float s, const VECTOR3D&A);
VECTOR3D operator* (const VECTOR3D &A, float s);
VECTOR3D operator/ (const VECTOR3D &A, float s);
VECTOR3D operator+ (const VECTOR3D &A, const VECTOR3D &B);
VECTOR3D operator- (const VECTOR3D &A, const VECTOR3D &B);
float Dot(const VECTOR3D &A, const VECTOR3D &B);
VECTOR3D Cross3(const VECTOR3D &A, const VECTOR3D &B);
float Magnity(const VECTOR3D &A);
VECTOR3D Normalize(const VECTOR3D &A);

