#pragma once
#include <list>
#include <vector>
#include <functional>
#include "Vector3D.h"
struct GraphNode
{
	unsigned int id;
	bool visited;
	GraphNode* father;
	std::list<GraphNode*> children;

	int weight;
	int conectionWeight;
	Vector3D worldPosition;
};

class CWalkerBase
{
protected:
	std::list<GraphNode*> m_openList;
public:
	CWalkerBase();
	std::vector<GraphNode*> Search(GraphNode* pathBegin, GraphNode* pathEnd, int maxIterations);
	std::vector<GraphNode*> Search(GraphNode* pathBegin, GraphNode* pathEnd);
	virtual GraphNode* SelectNextNode(GraphNode* pActual) = 0;
	virtual void EnlistNodes(GraphNode* pActual) = 0;
	std::function<int()> pHeuristicFoo; //Retorna el peso evaludao con la heuristica

	GraphNode* m_graphBegin;
	virtual ~CWalkerBase();
};

