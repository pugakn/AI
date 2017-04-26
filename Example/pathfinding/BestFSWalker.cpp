#include "BestFSWalker.h"

std::vector<GraphNode*> CBestFSWalker::Search(GraphNode * pathBegin, GraphNode * pathEnd, int maxIterations)
{
	//Seleccionar primer nodo
	std::vector<GraphNode*> backProp;
	auto pActualNode = pathBegin;
	m_closedList.push_back(pActualNode);
	pActualNode->pathNode = std::make_unique<PathNode>();
	pActualNode->pathNode->enlisted = true;
	pActualNode->pathNode->weight = pActualNode->weight;
	//Meter en la lista los hijos del nodo actual
	EnlistNodes(pActualNode, pathEnd);
	for (size_t i = 0; i < maxIterations; i++)
	{
		//Revisar si es el final
		if (pActualNode == pathEnd)
		{
			backProp = GetPath(pActualNode);
			break;
		}
		//Seleccionar siguiente nodo
		pActualNode = SelectNextNode(pActualNode);
		//Meter en la lista los hijos del nodo actual
		EnlistNodes(pActualNode, pathEnd);
	}
	//Reset();
	return backProp;
}

std::vector<GraphNode*> CBestFSWalker::Search(GraphNode * pathBegin, GraphNode * pathEnd)
{
	//Seleccionar primer nodo
	std::vector<GraphNode*> backProp;
	auto pActualNode = pathBegin;
	m_closedList.push_back(pActualNode);
	pActualNode->pathNode = std::make_unique<PathNode>();
	pActualNode->pathNode->enlisted = true;
	pActualNode->pathNode->weight = pActualNode->weight;
	do
	{
		//Revisar si es el final
		if (pActualNode == pathEnd)
		{
			backProp = GetPath(pActualNode);
			break;
		}
		//Meter en la lista los hijos del nodo actual
		EnlistNodes(pActualNode, pathEnd);
		//Seleccionar siguiente nodo
		pActualNode = SelectNextNode(pActualNode);
	} while (m_openList.size() > 0);
	//Reset();
	return backProp;
}

std::list<GraphNode*> CBestFSWalker::GetClosedList()
{
	return m_closedList;
}

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
			if (option->pathNode == nullptr)
				option->pathNode = std::make_unique<PathNode>();
			if (!option->pathNode->enlisted) {
				option->pathNode->weight = pHeuristicFoo(pFinalNode, option);
				option->pathNode->enlisted = true;
				option->pathNode->father = pActual;
				m_closedList.push_back(option);
				m_openList.push(option);
			}
		}
	}
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
		it->pathNode.reset();
	}
	m_closedList.clear();
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
