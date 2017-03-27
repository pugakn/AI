#pragma once
#include "WalkerBase.h"
class CBestFSWalker :
	public CWalkerBase
{
public:
	GraphNode* SelectNextNode(GraphNode* pActual) override;
	void EnlistNodes(GraphNode* pActual) override;
	CBestFSWalker();
	~CBestFSWalker();
};

