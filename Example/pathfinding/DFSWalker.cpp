#include "DFSWalker.h"


GraphNode* CDFSWalker::SelectNextNode(GraphNode* pActual)
{
	GraphNode* pActualNode = m_openList.back();
	m_openList.pop_back();
	return pActualNode;
}

size_t CDFSWalker::GetOpenListSize()
{
	return m_openList.size();
}

void CDFSWalker::EnlistNodes(GraphNode * pActual, GraphNode* pFinal)
{
	for (auto &option : pActual->children)
	{
		if (option->active) {
			if (option->pathNode == nullptr){

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

void CDFSWalker::Reset()
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

CDFSWalker::CDFSWalker()
{
}


CDFSWalker::~CDFSWalker()
{
}
