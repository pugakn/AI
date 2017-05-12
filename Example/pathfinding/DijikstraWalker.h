#pragma once
#include "WalkerBase.h"
class CDijikstraWalker :
	public CWalkerBase
{
private:
	std::list<GraphNode*> m_openList;

	GraphNode* SelectNextNode(GraphNode* pActual) override;
	void EnlistNodes(GraphNode* pActual, GraphNode* pFinal) override;
	size_t GetOpenListSize() override;

public:
	//std::list<GraphNode*> GetClosedList() override;

	void Reset() override;
	CDijikstraWalker();
	~CDijikstraWalker();
};

