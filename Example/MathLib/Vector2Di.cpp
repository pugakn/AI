#include "Vector2Di.h"
#include <math.h>


Vector2Di::Vector2Di()
{
}
Vector2Di::Vector2Di(float * V)
{
	x = V[0];
	y = V[1];
}
Vector2Di::Vector2Di(const Vector2Di &V)
{
	x = V.x;
	y = V.y;
}
Vector2Di::Vector2Di(float fx, float fy)
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
Vector2Di operator* (float s, const Vector2Di&A) {
	return Vector2Di(A.x*s, A.y*s);
}
Vector2Di operator* (const Vector2Di &A, float s) {
	return s*A;
}
Vector2Di operator/ (const Vector2Di &A, float s) {
	return A*(1 / s);
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
float Dot(const Vector2Di &A, const Vector2Di &B) {
	return A.x*B.x + A.y*B.y ;
}


float Magnitude(const Vector2Di &A) {
	return sqrt(Dot(A, A));
}
Vector2Di Truncate(Vector2Di A, float max)
{
	if (Magnitude(A) > max) {
		A = Normalize(A);
		A = A*max;
	}
	return A;
}
Vector2Di Normalize(const Vector2Di &A) {
	return A / Magnitude(A);
}

