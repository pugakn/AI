#include "stdafx.h"
#include "GraphPoint.h"

GraphPoint::GraphPoint(Vector2Di point) : p(point)
{
	pGraphNode = nullptr;
}

GraphPoint::GraphPoint(Vector2Di point, DungeoBlock* graphNode) : p(point)
{
	pGraphNode = graphNode;
}
