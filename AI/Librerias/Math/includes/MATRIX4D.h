#pragma once
#include "VECTOR4D.h"
#include <iostream>

using namespace std;
struct MATRIX4D
{
public:
	union {
		struct {
			float m00, m01, m02, m03;
			float m10, m11, m12, m13;
			float m20, m21, m22, m23;
			float m30, m31, m32, m33;
		};
		struct {
			VECTOR4D Row0, Row1, Row2, Row3;
		};
		struct 
		{
			VECTOR4D Row[4];
		};
		float m[4][4];
		float v[16];
	};
public:
	MATRIX4D();
	MATRIX4D(float a00, float a01, float a02, float a03,
			 float a10, float a11, float a12, float a13,
			 float a20, float a21, float a22, float a23,
			 float a30, float a31, float a32, float a33);
	MATRIX4D(const MATRIX4D& M);
	MATRIX4D(const VECTOR4D &row0,
			 const VECTOR4D &row1,
			 const VECTOR4D &row2,
			 const VECTOR4D &row3);
	~MATRIX4D();
};
ostream& operator << (ostream& out, const MATRIX4D& A);
istream& operator >> (istream& in, MATRIX4D& A);
MATRIX4D operator* (const MATRIX4D& A, const MATRIX4D& B);
VECTOR4D operator* (const VECTOR4D& V, const MATRIX4D& M);
VECTOR4D operator* (const MATRIX4D& M, const VECTOR4D& V);
MATRIX4D Zero();
MATRIX4D Identity();
MATRIX4D TranslationRH(float dx, float dy, float dz);
MATRIX4D RotationXRH(float theta);
MATRIX4D RotationYRH(float theta);
MATRIX4D RotationZRH(float theta);
MATRIX4D TranslationLH(float dx, float dy, float dz);
MATRIX4D RotationXLH(float theta);
MATRIX4D RotationYLH(float theta);
MATRIX4D RotationZLH(float theta);
MATRIX4D Scaling(float sx, float sy, float sz);
float Det(const MATRIX4D& M);
MATRIX4D Transpose(const MATRIX4D& M);
MATRIX4D Cofactors(const MATRIX4D& M);
MATRIX4D Inverse(const MATRIX4D& M);
