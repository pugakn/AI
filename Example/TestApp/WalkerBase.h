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
	}
	//GraphNode(const GraphNode& node) { this->weight = node.weight; id = node.id; pathNode = node.pathNode; };
	unsigned int id;
	std::list<GraphNode*> children;
	float weight;
	Vector3D worldPosition;
	bool active;
	std::unique_ptr<PathNode> pathNode;
};

struct PathNode //PathNode
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
protected:
	std::function<float(GraphNode* finalNode, GraphNode*actualNode)> pHeuristicFoo; //Retorna el peso evaludao con la heuristica
public:
	CWalkerBase();
	virtual std::vector<GraphNode*> Search(GraphNode* pathBegin, GraphNode* pathEnd, int maxIterations) = 0;
	virtual std::vector<GraphNode*> Search(GraphNode* pathBegin, GraphNode* pathEnd) = 0;
	virtual std::list<GraphNode*> GetClosedList() = 0;
	//Reset
	virtual void Reset() = 0;
	//BackProp
	std::vector<GraphNode*> GetPath(GraphNode* pActualNode);
	void SetHeuristic(Heuristic::E heuristic);

	virtual ~CWalkerBase();
};

