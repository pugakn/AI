#include "DijikstraWalker.h"



GraphNode * CDijikstraWalker::SelectNextNode(GraphNode * pActual)
{
	GraphNode* pActualNode = m_openList.front();
	m_openList.pop_front();
	return pActualNode;
}

void CDijikstraWalker::EnlistNodes(GraphNode * pActual, GraphNode* pFinal)
{
	for (auto &option : pActual->children)
	{
		if (option->active) {
			if (option->pathNode == nullptr) {
				PathNode *pathNode = new PathNode();
				pathNode->father = pActual;
				pathNode->enlisted = true;
				pathNode->weight = pActual->pathNode->weight + option->weight;
				m_pathNodePool.push_back(pathNode);
				option->pathNode = m_pathNodePool.back();
				m_closedList.push_back(option);
				m_openList.push_back(option);

				
			}
			else
				if (option->pathNode->weight > pActual->pathNode->weight + option->weight)
				{
					option->pathNode->father = pActual;
					option->pathNode->weight = pActual->pathNode->weight + option->weight;
					m_openList.push_back(option);
					m_closedList.push_back(option);
				}
		}
	}
}

size_t CDijikstraWalker::GetOpenListSize()
{
	return m_openList.size();
}


void CDijikstraWalker::Reset()
{
	for (auto &it : m_closedList)
	{
		it->pathNode = nullptr;
	}
	m_closedList.clear();
	m_openList.clear();
	for (auto &it : m_pathNodePool)
	{
		delete it;
	}
	m_pathNodePool.clear();
}

CDijikstraWalker::CDijikstraWalker()
{
}


CDijikstraWalker::~CDijikstraWalker()
{
}
