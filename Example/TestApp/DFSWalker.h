#pragma once
#include "WalkerBase.h"
class CDFSWalker :
	public CWalkerBase
{
public:
	GraphNode* SelectNextNode(GraphNode* pActual) override;
	void EnlistNodes(GraphNode* pActual) override;
	CDFSWalker();
	~CDFSWalker();
};

