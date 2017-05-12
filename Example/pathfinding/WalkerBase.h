#pragma once
#include <list>
#include <vector>
#include <functional>
#include <memory>
#include "Vector3D.h"
namespace Heuristic
{
	enum E
	{
		kEuclidean,
		kCuadratic,
		kManhatan
	};
}

struct PathNode;

struct GraphNode
{
	GraphNode()
	{
		weight = 1;
		active = true;
		pathNode = nullptr;
	}
	unsigned int id;
	std::list<GraphNode*> children;
	float weight;
	Vector3D worldPosition;
	bool active;
	PathNode* pathNode;
};

struct PathNode
{
	bool enlisted;
	GraphNode* father;
	float weight;
	float gCost;
	PathNode() {
		enlisted = false;
		father = nullptr;
		gCost = 0;
		weight = 0;
	}
	bool operator ()(const GraphNode* lhs, const GraphNode* rhs) const
	{
		if (lhs->pathNode == nullptr || rhs->pathNode == nullptr)
			return false;
		return lhs->pathNode->weight > rhs->pathNode->weight;
	}
};

class CWalkerBase
{
	const int MAX_ITERATIONS  = 500;
	int m_nodePoolIndex;
protected:
	std::function<float(GraphNode* finalNode, GraphNode*actualNode)> pHeuristicFoo; //Retorna el peso evaludao con la heuristica
	std::vector<PathNode> m_pathNodeStaticPool;
	std::vector<PathNode*> m_pathNodePool;
	std::list<GraphNode*> m_closedList;
public:
	CWalkerBase();
	std::vector<GraphNode*> Search(GraphNode* pathBegin, GraphNode* pathEnd, int maxIterations = 0);
	std::list<GraphNode*> GetClosedList();
	virtual void EnlistNodes(GraphNode* pActual, GraphNode* pFinalNode) = 0;
	virtual size_t GetOpenListSize() = 0;
	virtual GraphNode* SelectNextNode(GraphNode* pActual) = 0;
	//Reset
	virtual void Reset() = 0;
	//BackProp
	std::vector<GraphNode*> GetPath(GraphNode* pActualNode);
	void SetHeuristic(Heuristic::E heuristic);

	void InitNodePool();
	PathNode* GetNode();

	virtual ~CWalkerBase();
};

