#include "BFSWalker.h"


GraphNode * CBFSWalker::SelectNextNode(GraphNode* pActual)
{
	GraphNode* pActualNode = m_openList.front();
	m_openList.pop_front();
	return pActualNode;
}

void CBFSWalker::EnlistNodes(GraphNode* pActual, GraphNode* pFinalNode)
{
	for (auto &option : pActual->children)
	{
		if (option->active) {
			if (option->pathNode == nullptr)
			{
				PathNode *pathNode = new PathNode();
				pathNode->father = pActual;
				pathNode->enlisted = true;
				m_pathNodePool.push_back(pathNode);
				option->pathNode = m_pathNodePool.back();
				m_closedList.push_back(option);
				m_openList.push_back(option);
			}
		}
	}
}

size_t CBFSWalker::GetOpenListSize()
{
	return m_openList.size();
}

void CBFSWalker::Reset()
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
CBFSWalker::CBFSWalker()
{
}


CBFSWalker::~CBFSWalker()
{
}
