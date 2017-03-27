#include "BFSWalker.h"

GraphNode * CBFSWalker::SelectNextNode(GraphNode* pActual)
{
	GraphNode* pActualNode = m_openList.front();
	pActualNode->father = pActual;
	m_openList.pop_front();
	return pActualNode;
}

void CBFSWalker::EnlistNodes(GraphNode* pActual)
{
	for (auto &option : pActual->children)
	{
		if (!option->visited) {
			m_openList.push_back(option);
		}
	}
}

CBFSWalker::CBFSWalker()
{
}


CBFSWalker::~CBFSWalker()
{
}
