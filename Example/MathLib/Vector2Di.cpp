#include "Vector2Di.h"
#include <math.h>


Vector2Di::Vector2Di()
{
}
Vector2Di::Vector2Di(int * V)
{
	x = V[0];
	y = V[1];
}
Vector2Di::Vector2Di(const Vector2Di &V)
{
	x = V.x;
	y = V.y;
}
Vector2Di::Vector2Di(int fx, int fy)
{
	x = fx;
	y = fy;
}
Vector2Di::~Vector2Di()
{
}
Vector2Di operator* (const Vector2Di &A, const Vector2Di &B) {
	return Vector2Di(A.x*B.x, A.y*B.y);
}
Vector2Di operator* (int s, const Vector2Di&A) {
	return Vector2Di(A.x*s, A.y*s);
}
Vector2Di operator* (const Vector2Di &A, int s) {
	return s*A;
}
Vector2Di operator*(float s, const Vector2Di & A)
{
	return Vector2Di(A.x*s, A.y*s);
}
Vector2Di operator*(const Vector2Di & A, float s)
{
	return Vector2Di(A.x*s, A.y*s);
}
Vector2Di operator/ (const Vector2Di &A, int s) {
	return Vector2Di(A.x / s,A.y/s);
}
Vector2Di operator/(const Vector2Di & A, float s)
{
	return Vector2Di(A.x / s, A.y / s);
}
Vector2Di operator+ (const Vector2Di &A, const Vector2Di &B) {
	return Vector2Di(A.x + B.x, A.y + B.y);
}
Vector2Di operator+= (Vector2Di &A, const Vector2Di &B) {
	A = Vector2Di(A.x + B.x, A.y + B.y);
	return A;
}
bool operator==(const Vector2Di & A, const Vector2Di & B)
{
	return (A.x == B.x && A.y == B.y);
}
Vector2Di operator- (const Vector2Di &A, const Vector2Di &B) {
	return Vector2Di(A.x - B.x, A.y - B.y);
}
int Dot(const Vector2Di &A, const Vector2Di &B) {
	return A.x*B.x + A.y*B.y ;
}


int Magnitude(const Vector2Di &A) {
	return sqrt(Dot(A, A));
}


Vector2Di GetDirection(const Vector2Di &A) {
	Vector2Di temp(0,0);
	if (A.x > 0)
		temp.x = 1;
	if (A.x < 0)
		temp.x = -1;
	if (A.y > 0)
		temp.y = 1;
	if (A.y < 0)
		temp.y = -1;
	return temp;
}

