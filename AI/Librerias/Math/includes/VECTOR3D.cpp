#include "VECTOR3D.h"


VECTOR3D::VECTOR3D()
{
}
VECTOR3D::VECTOR3D(const VECTOR3D &V)
{
	x = V.x;
	y = V.y;
	z = V.z;
}
VECTOR3D::VECTOR3D(float fx, float fy, float fz)
{
	x = fx;
	y = fy;
	z = fz;
}
VECTOR3D::~VECTOR3D()
{
}


ostream& operator << (ostream& out, const VECTOR3D& V) {
	out << "[" << V.x << "," << V.y << "," << V.z << "]";
	return out;
}
istream& operator >> (istream& in, VECTOR3D& V) {
	in >> V.x >> V.y >> V.z;
	return in;
}
VECTOR3D operator* (const VECTOR3D &A, const VECTOR3D &B) {
	return VECTOR3D(A.x*B.x, A.y*B.y, A.z*B.z);
}
VECTOR3D operator* (float s, const VECTOR3D&A) {
	return VECTOR3D(A.x*s, A.y*s, A.z*s);
}
VECTOR3D operator* (const VECTOR3D &A, float s) {
	return s*A;
}
VECTOR3D operator/ (const VECTOR3D &A, float s) {
	return A*(1 / s);
}
VECTOR3D operator+ (const VECTOR3D &A, const VECTOR3D &B) {
	return VECTOR3D(A.x + B.x, A.y + B.y, A.z + B.z);
}
VECTOR3D operator- (const VECTOR3D &A, const VECTOR3D &B) {
	return VECTOR3D(A.x - B.x, A.y - B.y, A.z - B.z);
}
float Dot(const VECTOR3D &A, const VECTOR3D &B) {
	return A.x*B.x + A.y*B.y + A.z*B.z;
}
VECTOR3D Cross3(const VECTOR3D &A, const VECTOR3D &B) {
	return VECTOR3D(A.y*B.z - A.z*B.y,
		A.z*B.x - A.x*B.z,
		A.x*B.y - A.y*B.x);
}

float Magnity(const VECTOR3D &A) {
	return sqrt(Dot(A, A));
}
VECTOR3D Normalize(const VECTOR3D &A) {
	return A / Magnity(A);
}

