#include "WalkerBase.h"



CWalkerBase::CWalkerBase()
{
}

std::vector<GraphNode*> CWalkerBase::Search(GraphNode * pathBegin, GraphNode * pathEnd, int maxIterations)
{
	//Seleccionar primer nodo
	std::vector<GraphNode*> backProp;
	auto pActualNode = pathBegin;
	m_closedList.push_back(pActualNode);
	pActualNode->copy.visited = true;
	for (size_t i = 0; i < maxIterations; i++)
	{
		//Meter en la lista los hijos del nodo actual
		EnlistNodes(pActualNode);
		//Seleccionar siguiente nodo
		SelectNextNode(pActualNode);
		//Revisar si es el final
		if (pActualNode == pathEnd)
		{
			backProp.push_back(pActualNode->copy.father);
			while (pActualNode->copy.father != nullptr)
			{
				pActualNode = pActualNode->copy.father;
				backProp.push_back(pActualNode->copy.father);
			}
			break;
		}
		pActualNode->copy.visited = true;
	}
	for (auto &it : m_closedList)
	{
		it->copy.visited = false;
		it->copy.father = nullptr;
	}
	return backProp;
}

std::vector<GraphNode*> CWalkerBase::Search(GraphNode * pathBegin, GraphNode * pathEnd)
{
	//Seleccionar primer nodo
	std::vector<GraphNode*> backProp;
	auto pActualNode = pathBegin;
	pActualNode->copy.visited = true;
	do
	{
		//Meter en la lista los hijos del nodo actual
		EnlistNodes(pActualNode);
		//Seleccionar siguiente nodo
		SelectNextNode(pActualNode);
		//Revisar si es el final
		if (pActualNode == pathEnd)
		{
			backProp.push_back(pActualNode->copy.father);
			while (pActualNode->copy.father != nullptr)
			{
				pActualNode = pActualNode->copy.father;
				backProp.push_back(pActualNode->copy.father);
			}
			break;
		}
		pActualNode->copy.visited = true;
	} while (m_openList.size() > 0);

	for (auto &it : m_closedList)
	{
		it->copy.visited = false;
		it->copy.father = nullptr;
	}
	return backProp;
}



CWalkerBase::~CWalkerBase()
{
}
