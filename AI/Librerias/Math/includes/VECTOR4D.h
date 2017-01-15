#pragma once
#include <iostream>

using namespace std;

struct VECTOR4D
{
public:
	union 
	{
		struct 
		{
			float x, y, z, w;
		};
		struct
		{
			float r, g, b, a;
		};
		struct 
		{
			long lx, ly, lz, lw;
		};
		float v[4];
		unsigned long ul[4];
		long l[4];

	};
	VECTOR4D();
	VECTOR4D(const VECTOR4D& V);
	VECTOR4D(float fx, float fy, float fz, float fw);
	~VECTOR4D();
};

ostream& operator << (ostream& out, const VECTOR4D& V);
istream& operator >> (istream& in, VECTOR4D& V);
VECTOR4D operator* (const VECTOR4D &A, const VECTOR4D &B);
VECTOR4D operator* (float s, const VECTOR4D&A);
VECTOR4D operator* (const VECTOR4D &A, float s);
VECTOR4D operator/ (const VECTOR4D &A, float s);
VECTOR4D operator+ (const VECTOR4D &A, const VECTOR4D &B);
VECTOR4D operator- (const VECTOR4D &A, const VECTOR4D &B);
float Dot(const VECTOR4D &A, const VECTOR4D &B);
VECTOR4D Cross3(const VECTOR4D &A, const VECTOR4D &B);
float Magnity(const VECTOR4D &A);
VECTOR4D Normalize(const VECTOR4D &A);


