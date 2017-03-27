#include "WalkerBase.h"



CWalkerBase::CWalkerBase()
{
}

std::vector<GraphNode*> CWalkerBase::Search(GraphNode * pathBegin, GraphNode * pathEnd, int maxIterations)
{
	//Seleccionar primer nodo
	std::vector<GraphNode*> backProp;
	auto pActualNode = pathBegin;
	pActualNode->visited = true;
	for (size_t i = 0; i < maxIterations; i++)
	{
		//Meter en la lista los hijos del nodo actual
		EnlistNodes(pActualNode);
		//Seleccionar siguiente nodo
		SelectNextNode(pActualNode);
		//Revisar si es el final
		if (pActualNode == pathEnd)
		{
			backProp.push_back(pActualNode->father);
			while (pActualNode->father != nullptr)
			{
				pActualNode = pActualNode->father;
				backProp.push_back(pActualNode->father);
			}
			break;
		}
		pActualNode->visited = true;
	}
	return backProp;
}

std::vector<GraphNode*> CWalkerBase::Search(GraphNode * pathBegin, GraphNode * pathEnd)
{
	//Seleccionar primer nodo
	std::vector<GraphNode*> backProp;
	auto pActualNode = pathBegin;
	pActualNode->visited = true;
	do
	{
		//Meter en la lista los hijos del nodo actual
		EnlistNodes(pActualNode);
		//Seleccionar siguiente nodo
		SelectNextNode(pActualNode);
		//Revisar si es el final
		if (pActualNode == pathEnd)
		{
			backProp.push_back(pActualNode->father);
			while (pActualNode->father != nullptr)
			{
				pActualNode = pActualNode->father;
				backProp.push_back(pActualNode->father);
			}
			break;
		}
		pActualNode->visited = true;
	} while (m_openList.size() > 0);
	return backProp;
}



CWalkerBase::~CWalkerBase()
{
}
