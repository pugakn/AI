#pragma once

struct Vector2Di
{
public:
	union
	{
		struct
		{
			float x, y;
		};
		float v[2];

	};
	Vector2Di();
	Vector2Di(float *V);
	Vector2Di(const Vector2Di& V);
	Vector2Di(float fx, float fy);
	~Vector2Di();
};
Vector2Di operator* (const Vector2Di &A, const Vector2Di &B);
Vector2Di operator* (float s, const Vector2Di&A);
Vector2Di operator* (const Vector2Di &A, float s);
Vector2Di operator/ (const Vector2Di &A, float s);
Vector2Di operator+ (const Vector2Di &A, const Vector2Di &B);
Vector2Di operator+= (Vector2Di &A, const Vector2Di &B);
bool operator== (const Vector2Di &A, const Vector2Di &B);
Vector2Di operator- (const Vector2Di &A, const Vector2Di &B);
float Dot(const Vector2Di &A, const Vector2Di &B);
//Vector2Di Cross3(const Vector2Di &A, const Vector2Di &B);
float Magnitude(const Vector2Di &A);
Vector2Di Truncate(Vector2Di A, float max);
Vector2Di Normalize(const Vector2Di &A);

