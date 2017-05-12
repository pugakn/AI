#pragma once
#include "WalkerBase.h"
class CBFSWalker :
	public CWalkerBase
{
private:
	std::list<GraphNode*> m_openList;
	GraphNode* SelectNextNode(GraphNode* pActual) override;
	void EnlistNodes(GraphNode* pActual, GraphNode* pFinalNode) override;
	size_t GetOpenListSize() override;
public:
	void Reset() override;

	CBFSWalker();
	~CBFSWalker();
};

