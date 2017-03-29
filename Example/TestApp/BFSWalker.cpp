#include "BFSWalker.h"

GraphNode * CBFSWalker::SelectNextNode(GraphNode* pActual)
{
	GraphNode* pActualNode = m_openList.front();
	pActualNode->copy.father = pActual;
	m_openList.pop_front();
	return pActualNode;
}

void CBFSWalker::EnlistNodes(GraphNode* pActual)
{
	for (auto &option : pActual->children)
	{
		if (!option->copy.visited) {
			m_openList.push_back(option);
			m_closedList.push_back(option);
		}
	}
}

CBFSWalker::CBFSWalker()
{
}


CBFSWalker::~CBFSWalker()
{
}
