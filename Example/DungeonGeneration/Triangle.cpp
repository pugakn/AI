#include "stdafx.h"
#include "Triangle.h"
#include <math.h>

void Triangle::Init()
{
	edges.push_back(Edge(p1,p2));
	edges.push_back(Edge(p2,p3 ));
	edges.push_back(Edge( p3,p1 ));
	float AcMag = Dot(p1.p, p1.p);
	float BcMag = Dot(p2.p, p2.p);
	float CcMag = Dot(p3.p, p3.p);
	Vector2Di U = (AcMag * (p3.p - p2.p) + BcMag * (p1.p - p3.p) + CcMag * (p2.p - p1.p));
	circumcenter.x = U.y / ((p1.p.x * (p3.p.y - p2.p.y) + p2.p.x * (p1.p.y - p3.p.y) + p3.p.x * (p2.p.y - p1.p.y))*2);
	circumcenter.y = U.x / ((p1.p.y * (p3.p.x - p2.p.x) + p2.p.y * (p1.p.x - p3.p.x) + p3.p.y * (p2.p.x - p1.p.x))*2);

	circumcenterRadius = circumcenterRadius = Magnitude(p1.p - circumcenter);
}

bool Triangle::IsPointOnCircumCircle(Vector2Di point)
{
	float dist = sqrtf(((point.x - circumcenter.x) * (point.x - circumcenter.x)) + ((point.y - circumcenter.y) * (point.y - circumcenter.y)));
	return dist <= circumcenterRadius;
}

bool Triangle::operator==(const Triangle & other) const
{
	return (((other.p1.p == this->p1.p) && (other.p2.p == this->p2.p) && (other.p3.p == this->p3.p))
		|| ((other.p2.p == this->p1.p) &&  (other.p3.p == this->p2.p) && (other.p1.p == this->p3.p)))
		|| ((other.p3.p == this->p1.p) &&  (other.p1.p == this->p2.p) && (other.p2.p == this->p3.p));
}

