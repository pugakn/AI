#include "BestFSWalker.h"


GraphNode * CBestFSWalker::SelectNextNode(GraphNode * pActual)
{
	m_openList.sort([](const GraphNode * a, const GraphNode * b) { return a->weight < b->weight; });
	GraphNode* pActualNode = m_openList.front();
	m_openList.pop_front();
	return pActualNode;
}

void CBestFSWalker::EnlistNodes(GraphNode * pActual)
{
	for (auto &option : pActual->children)
	{
		if (!option->copy.visited) {
			m_openList.push_back(option);
			m_closedList.push_back(option);
			m_openList.back()->weight = pHeuristicFoo();
		}
	}
}

CBestFSWalker::CBestFSWalker()
{
}


CBestFSWalker::~CBestFSWalker()
{
}
