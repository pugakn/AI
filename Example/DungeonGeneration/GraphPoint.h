#pragma once
#include <Vector2Di.h>
struct DungeoBlock;
struct GraphPoint
{
public:
	Vector2Di p;
	DungeoBlock* pGraphNode;
	GraphPoint(Vector2Di point);
	GraphPoint(Vector2Di point, DungeoBlock* graphNode);
};

