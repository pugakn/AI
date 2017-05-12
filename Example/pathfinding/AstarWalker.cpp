#include "AstarWalker.h"



GraphNode * CAstarWalker::SelectNextNode(GraphNode * pActual)
{
	//m_openList.sort([](const GraphNode * a, const GraphNode * b) { return a->pathNode->weight > b->pathNode->weight; });
	GraphNode* pActualNode = m_openList.top();
	m_openList.pop();
	return pActualNode;
}

void CAstarWalker::EnlistNodes(GraphNode * pActual, GraphNode* pFinalNode)
{
	for (auto &option : pActual->children)
	{
		if (option->active) {
			if (option->pathNode == nullptr){
				PathNode *pathNode = new PathNode();
				pathNode->father = pActual;
				pathNode->enlisted = true;
				float hCost = pHeuristicFoo(pFinalNode, option);
				pathNode->gCost = pActual->pathNode->gCost + option->weight;
				pathNode->weight = hCost + pathNode->gCost;

				m_pathNodePool.push_back(pathNode);
				option->pathNode = m_pathNodePool.back();
				m_closedList.push_back(option);
				m_openList.push(option);

			}
		}
	}
}

size_t CAstarWalker::GetOpenListSize()
{
	return m_openList.size();
}





void CAstarWalker::Reset()
{
	for (auto &it : m_closedList)
	{
		it->pathNode = nullptr;
	}
	m_closedList.clear();
	for (auto &it : m_pathNodePool)
	{
		delete it;
	}
	m_pathNodePool.clear();
	while (!m_openList.empty())
	{
		m_openList.pop();
	}
}

CAstarWalker::CAstarWalker()
{
}


CAstarWalker::~CAstarWalker()
{
}
