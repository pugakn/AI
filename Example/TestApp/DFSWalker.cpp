#include "DFSWalker.h"


GraphNode* CDFSWalker::SelectNextNode(GraphNode* pActual)
{
	GraphNode* pActualNode = m_openList.back();
	pActualNode->father = pActual;
	m_openList.pop_back();
	return pActualNode;
}

void CDFSWalker::EnlistNodes(GraphNode * pActual)
{
	for (auto &option : pActual->children)
	{
		if (!option->visited) {
			m_openList.push_back(option);
		}
	}
}

CDFSWalker::CDFSWalker()
{
}


CDFSWalker::~CDFSWalker()
{
}
