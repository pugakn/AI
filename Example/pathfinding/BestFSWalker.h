#pragma once
#include "WalkerBase.h"
#include <queue>
class CBestFSWalker :
	public CWalkerBase
{
private:
	std::priority_queue<GraphNode*, std::vector<GraphNode*>, PathNode> m_openList;
	GraphNode* SelectNextNode(GraphNode* pActual) override;
	void EnlistNodes(GraphNode* pActual, GraphNode* pFinalNode) override;
	/*void EnlistNodesFromPool(GraphNode* pActual, GraphNode* pFinalNode);*/
	size_t GetOpenListSize() override;
public:

	void Reset() override;

	CBestFSWalker();
	~CBestFSWalker();
};

