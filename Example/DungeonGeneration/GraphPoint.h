#pragma once
#include <Vector3D.h>
struct DungeoBlock;
struct GraphPoint
{
public:
	Vector3D p;
	DungeoBlock* pGraphNode;
	GraphPoint(Vector3D point);
	GraphPoint(Vector3D point, DungeoBlock* graphNode);
};

