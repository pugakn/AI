#include "DFSWalker.h"


GraphNode* CDFSWalker::SelectNextNode(GraphNode* pActual)
{
	GraphNode* pActualNode = m_openList.back();
	pActualNode->copy.father = pActual;
	m_openList.pop_back();
	return pActualNode;
}

void CDFSWalker::EnlistNodes(GraphNode * pActual)
{
	for (auto &option : pActual->children)
	{
		if (!option->copy.visited) {
			m_openList.push_back(option);
			m_closedList.push_back(option);
		}
	}
}

CDFSWalker::CDFSWalker()
{
}


CDFSWalker::~CDFSWalker()
{
}
