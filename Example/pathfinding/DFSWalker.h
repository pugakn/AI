#pragma once
#include "WalkerBase.h"
class CDFSWalker :
	public CWalkerBase
{
private:
	std::list<GraphNode*> m_openList;

	GraphNode* SelectNextNode(GraphNode* pActual)override;
	void EnlistNodes(GraphNode* pActual, GraphNode* pFinal) override;
	size_t GetOpenListSize() override;
public:

	void Reset() override;

	CDFSWalker();
	~CDFSWalker();
};

