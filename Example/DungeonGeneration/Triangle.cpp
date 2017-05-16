#include "stdafx.h"
#include "Triangle.h"
#include <math.h>

void Triangle::Init()
{
	edges.push_back(Edge(p1,p2));
	edges.push_back(Edge(p2,p3 ));
	edges.push_back(Edge( p3,p1 ));
	float ab = (p1.p.x * p1.p.x) + (p1.p.y * p1.p.y);
	float cd = (p2.p.x * p2.p.x) + (p2.p.y * p2.p.y);
	float ef = (p3.p.x * p3.p.x) + (p3.p.y * p3.p.y);

	circumcenter.x = (ab * (p3.p.y - p2.p.y) + cd * (p1.p.y - p3.p.y) + ef * (p2.p.y - p1.p.y)) / (p1.p.x * (p3.p.y - p2.p.y) + p2.p.x * (p1.p.y - p3.p.y) + p3.p.x * (p2.p.y - p1.p.y)) / 2.f;
	circumcenter.y = (ab * (p3.p.x - p2.p.x) + cd * (p1.p.x - p3.p.x) + ef * (p2.p.x - p1.p.x)) / (p1.p.y * (p3.p.x - p2.p.x) + p2.p.y * (p1.p.x - p3.p.x) + p3.p.y * (p2.p.x - p1.p.x)) / 2.f;
	circumcenter.z = 0;
	circumcenterRadius = circumcenterRadius = Magnitude(p1.p - circumcenter);
	//float div = 2 * Magnitude(Cross3(p1 - p2, p2 - p3)) * Magnitude(Cross3(p1 - p2, p2 - p3));
	//float angleA = (Magnitude((p2 - p3) *(p2 - p3)) * Dot(p1 - p2, p1 - p3)) / div;
	//float angleB = (Magnitude((p1 - p3) *(p1 - p3)) * Dot(p2 - p1, p2 - p3)) / div;
	//float angleC = (Magnitude((p1 - p2) *(p1 - p2)) * Dot(p3 - p1, p3 - p2)) / div;

	//circuncenter = p1*angleA + p2*angleB + p3*angleC;
	//circumcenterRadius = sqrtf(((p1.x - circuncenter.x) * (p1.x - circuncenter.x)) + ((p1.y - circuncenter.y) * (p1.y - circuncenter.y)));
}

bool Triangle::IsPointOnCircumCircle(Vector3D point)
{
	float dist = sqrtf(((point.x - circumcenter.x) * (point.x - circumcenter.x)) + ((point.y - circumcenter.y) * (point.y - circumcenter.y)));
	return dist <= circumcenterRadius;
	//float dist = sqrtf(((point.x - circuncenter.x) * (point.x - circuncenter.x)) + ((point.y - circuncenter.y) * (point.y - circuncenter.y)));
	//return dist <= circumcenterRadius;
}

bool Triangle::operator==(const Triangle & other) const
{
	return (((other.p1.p == this->p1.p) && (other.p2.p == this->p2.p) && (other.p3.p == this->p3.p))
		|| ((other.p2.p == this->p1.p) &&  (other.p3.p == this->p2.p) && (other.p1.p == this->p3.p)))
		|| ((other.p3.p == this->p1.p) &&  (other.p1.p == this->p2.p) && (other.p2.p == this->p3.p));
}

