#pragma once
//#include <Vector3D.h>
#include "GraphPoint.h"
struct DungeoBlock;
struct Edge
{
public:
	GraphPoint p1;
	GraphPoint p2;
	Edge(Vector2Di a, Vector2Di b) : p1(a), p2(b){};
	Edge(GraphPoint a, GraphPoint b) : p1(a), p2(b) {};
	bool operator==(const Edge &other) const;
};
