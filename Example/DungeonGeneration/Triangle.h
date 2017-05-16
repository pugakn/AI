#pragma once
#include <Vector3D.h>
#include "Edge.h"
#include <vector>
struct DungeoBlock;
struct Triangle
{
private:
	Vector3D circumcenter;
	float circumcenterRadius;
public:
	GraphPoint p1;
	GraphPoint p2;
	GraphPoint p3;
	std::vector<Edge> edges;
	void Init();
	bool IsPointOnCircumCircle(Vector3D point);
	bool operator==(const Triangle &other) const; 
	Triangle(GraphPoint a, GraphPoint b, GraphPoint c) : p1(a), p2(b), p3(c) 
	{ 
		Init(); 
	};
	Triangle(Vector3D a, Vector3D b, Vector3D c) : p1(a), p2(b), p3(c) 
	{
		Init(); 
	};
};
