#include "stdafx.h"
#include "GraphPoint.h"

GraphPoint::GraphPoint(Vector3D point) : p(point)
{
	pGraphNode = nullptr;
}

GraphPoint::GraphPoint(Vector3D point, DungeoBlock* graphNode) : p(point)
{
	pGraphNode = graphNode;
}
