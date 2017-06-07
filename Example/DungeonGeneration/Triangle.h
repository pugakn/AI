#pragma once
#include <Vector2Di.h>
#include "Edge.h"
#include <vector>
struct DungeoBlock;
struct Triangle
{
private:
	Vector2Di circumcenter;
	float circumcenterRadius;
public:
	GraphPoint p1;
	GraphPoint p2;
	GraphPoint p3;
	std::vector<Edge> edges;
	void Init();
	bool IsPointOnCircumCircle(Vector2Di point);
	bool operator==(const Triangle &other) const; 
	Triangle(GraphPoint a, GraphPoint b, GraphPoint c) : p1(a), p2(b), p3(c) 
	{ 
		Init(); 
	};
	Triangle(Vector2Di a, Vector2Di b, Vector2Di c) : p1(a), p2(b), p3(c)
	{
		Init(); 
	};
};
