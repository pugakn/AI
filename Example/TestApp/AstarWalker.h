#pragma once
#include "WalkerBase.h"
#include <queue>
class CAstarWalker :
	public CWalkerBase
{
private:
	std::priority_queue<GraphNode*, std::vector<GraphNode*>, PathNode> m_openList;
	std::list<GraphNode*> m_closedList;

	GraphNode* SelectNextNode(GraphNode* pActual);
	void EnlistNodes(GraphNode* pActual, GraphNode* pFinalNode);
public:
	std::vector<GraphNode*> Search(GraphNode* pathBegin, GraphNode* pathEnd, int maxIterations) override;
	std::vector<GraphNode*> Search(GraphNode* pathBegin, GraphNode* pathEnd) override;
	std::list<GraphNode*> GetClosedList() override;


	void Reset() override;
	CAstarWalker();
	~CAstarWalker();
};

