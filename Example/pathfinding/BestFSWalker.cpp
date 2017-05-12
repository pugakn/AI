#include "BestFSWalker.h"

GraphNode * CBestFSWalker::SelectNextNode(GraphNode * pActual)
{
	//m_openList.sort([](const GraphNode * a, const GraphNode * b) { return a->pathNode->weight > b->pathNode->weight; });
	GraphNode* pActualNode = m_openList.top();
	m_openList.pop();
	return pActualNode;
}

void CBestFSWalker::EnlistNodes(GraphNode * pActual, GraphNode* pFinalNode)
{
	for (auto &option : pActual->children)
	{
		if (option->active) {
			if (option->pathNode == nullptr){
				PathNode *pathNode = new PathNode();
				pathNode->father = pActual;
				pathNode->enlisted = true;
				pathNode->weight = pHeuristicFoo(pFinalNode, option);
				m_pathNodePool.push_back(pathNode);
				option->pathNode = m_pathNodePool.back();
				m_closedList.push_back(option);
				m_openList.push(option);
			}
		}
	}
}

size_t CBestFSWalker::GetOpenListSize()
{
	return m_openList.size();
}

//void CBestFSWalker::EnlistNodesFromPool(GraphNode * pActual, GraphNode * pFinalNode)
//{
//	for (auto &option : pActual->children)
//	{
//		if (option->active) {
//			if (option->pathNode == nullptr)
//				option->pathNode = GetNode();
//			if (!option->pathNode->enlisted) {
//				option->pathNode->weight = pHeuristicFoo(pFinalNode, option);
//				option->pathNode->enlisted = true;
//				option->pathNode->father = pActual;
//				m_closedList.push_back(option);
//				m_openList.push(option);
//			}
//		}
//	}
//}

void CBestFSWalker::Reset()
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
CBestFSWalker::CBestFSWalker()
{
}


CBestFSWalker::~CBestFSWalker()
{
}
