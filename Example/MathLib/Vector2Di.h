#pragma once

struct Vector2Di
{
public:
	union
	{
		struct
		{
			int x, y;
		};
		int v[2];

	};
	Vector2Di();
	Vector2Di(int *V);
	Vector2Di(const Vector2Di& V);
	Vector2Di(int fx, int fy);
	~Vector2Di();
};
Vector2Di operator* (const Vector2Di &A, const Vector2Di &B);
Vector2Di operator* (int s, const Vector2Di&A);
Vector2Di operator* (const Vector2Di &A, int s);
Vector2Di operator* (float s, const Vector2Di&A);
Vector2Di operator* (const Vector2Di &A, float s);
Vector2Di operator/ (const Vector2Di &A, int s);
Vector2Di operator/ (const Vector2Di &A, float s);
Vector2Di operator+ (const Vector2Di &A, const Vector2Di &B);
Vector2Di operator+= (Vector2Di &A, const Vector2Di &B);
bool operator== (const Vector2Di &A, const Vector2Di &B);
Vector2Di operator- (const Vector2Di &A, const Vector2Di &B);
int Dot(const Vector2Di &A, const Vector2Di &B);
//Vector2Di Cross3(const Vector2Di &A, const Vector2Di &B);
int Magnitude(const Vector2Di &A);
Vector2Di GetDirection(const Vector2Di &A);

