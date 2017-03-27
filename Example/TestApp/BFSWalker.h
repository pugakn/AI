#pragma once
#include "WalkerBase.h"
class CBFSWalker :
	public CWalkerBase
{
public:
	GraphNode* SelectNextNode(GraphNode* pActual) override;
	void EnlistNodes(GraphNode* pActual) override;
	CBFSWalker();
	~CBFSWalker();
};

