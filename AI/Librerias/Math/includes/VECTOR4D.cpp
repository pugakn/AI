#include "VECTOR4D.h"


VECTOR4D::VECTOR4D()
{
}
VECTOR4D::VECTOR4D(const VECTOR4D &V)
{
	x = V.x;
	y = V.y;
	z = V.z;
	w = V.w;
}
VECTOR4D::VECTOR4D(float fx, float fy, float fz, float fw)
{
	x = fx;
	y = fy;
	z = fz;
	w = fw;
}
VECTOR4D::~VECTOR4D()
{
}


ostream& operator << (ostream& out, const VECTOR4D& V) {
	out << "["<< V.x << "," << V.y << "," << V.z << "," << V.w << "]";
	return out;
}
istream& operator >> (istream& in, VECTOR4D& V) {
	in >> V.x >> V.y >> V.z >> V.w;
	return in;
}
VECTOR4D operator* (const VECTOR4D &A, const VECTOR4D &B) {
	return VECTOR4D(A.x*B.x, A.y*B.y, A.z*B.z, A.w*B.w);
}
VECTOR4D operator* (float s, const VECTOR4D&A) {
	return VECTOR4D(A.x*s,A.y*s,A.z*s,A.w*s);
}
VECTOR4D operator* (const VECTOR4D &A, float s) {
	return s*A;
}
VECTOR4D operator/ (const VECTOR4D &A, float s) {
	return A*(1 / s);
}
VECTOR4D operator+ (const VECTOR4D &A, const VECTOR4D &B) {
	return VECTOR4D(A.x + B.x, A.y + B.y,A.z + B.z,A.w + B.w);
}
VECTOR4D operator- (const VECTOR4D &A, const VECTOR4D &B) {
	return VECTOR4D(A.x - B.x, A.y - B.y, A.z - B.z, A.w - B.w);
}
float Dot(const VECTOR4D &A, const VECTOR4D &B) {
	return A.x*B.x + A.y*B.y + A.z*B.z + A.w*B.w;
}
VECTOR4D Cross3(const VECTOR4D &A, const VECTOR4D &B) {
	return VECTOR4D(A.y*B.z - A.z*B.y,
					A.z*B.x - A.x*B.z,
					A.x*B.y - A.y*B.x,
					0);
}

float Magnity(const VECTOR4D &A) {
	return sqrt(Dot(A,A));
}
VECTOR4D Normalize(const VECTOR4D &A) {
	return A / Magnity(A);
}
