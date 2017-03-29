#pragma once
#include <list>
#include <vector>
#include <functional>
#include "Vector3D.h"
struct GraphNode
{
	unsigned int id;
	std::list<GraphNode*> children;

	int weight;
	int conectionWeight;
	Vector3D worldPosition;
	CopyNode copy;
};
struct CopyNode
{
	bool visited {false};
	GraphNode* father;
};

class CWalkerBase
{
protected:
	std::list<GraphNode*> m_openList;
	std::list<GraphNode*> m_closedList;
public:
	CWalkerBase();
	std::vector<GraphNode*> Search(GraphNode* pathBegin, GraphNode* pathEnd, int maxIterations);
	std::vector<GraphNode*> Search(GraphNode* pathBegin, GraphNode* pathEnd);
	virtual GraphNode* SelectNextNode(GraphNode* pActual) = 0;
	virtual void EnlistNodes(GraphNode* pActual) = 0;
	std::function<int()> pHeuristicFoo; //Retorna el peso evaludao con la heuristica

	//GraphNode* m_graphRoot;
	virtual ~CWalkerBase();
};

