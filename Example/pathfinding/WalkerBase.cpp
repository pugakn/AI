#include "WalkerBase.h"
#include "DijikstraWalker.h"


CWalkerBase::CWalkerBase()
{
	
}

std::vector<GraphNode*> CWalkerBase::Search(GraphNode * pathBegin, GraphNode * pathEnd, int maxIterations)
{
	//Seleccionar primer nodo
	std::vector<GraphNode*> backProp;
	auto pActualNode = pathBegin;
	PathNode *tmpPathNode = new PathNode();
	tmpPathNode->enlisted = true;
	tmpPathNode->weight = pActualNode->weight;
	m_pathNodePool.push_back(tmpPathNode);
	pActualNode->pathNode = m_pathNodePool.back();
	//Meter en la lista los hijos del nodo actual
	EnlistNodes(pActualNode,pathEnd);
	if (typeid(*this) == typeid(CDijikstraWalker))
	{
		do
		{
			//Seleccionar siguiente nodo
			pActualNode = SelectNextNode(pActualNode);
			//Meter en la lista los hijos del nodo actual
			EnlistNodes(pActualNode, pathEnd);
		} while (GetOpenListSize() > 0);
		backProp = GetPath(pathEnd);
	}
	else if (maxIterations != 0)
	{
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
			EnlistNodes(pActualNode,pathEnd);
		}
	}
	else {
		do
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
		} while (GetOpenListSize() > 0);
	}
	//Reset();
	return backProp;
}

std::list<GraphNode*> CWalkerBase::GetClosedList()
{
	return m_closedList;
}

std::vector<GraphNode*> CWalkerBase::GetPath(GraphNode* pActualNode)
{
	std::vector<GraphNode*> tempBackProp;
	tempBackProp.push_back(pActualNode);
	while (pActualNode->pathNode->father != nullptr)
	{
		if (pActualNode->pathNode->father == nullptr)
		{
			tempBackProp.push_back(pActualNode);
			break;
		}
		pActualNode = pActualNode->pathNode->father;
		tempBackProp.push_back(pActualNode);
	}
	return tempBackProp;
}


	


void CWalkerBase::SetHeuristic(Heuristic::E heuristic)
{
	switch (heuristic)
	{
	case Heuristic::kEuclidean:
		pHeuristicFoo = [](GraphNode* finalNode, GraphNode*actualNode) 
		{
			return Magnitude(finalNode->worldPosition - actualNode->worldPosition); 
		};
		break;
	case Heuristic::kCuadratic:
		pHeuristicFoo = [](GraphNode* finalNode, GraphNode*actualNode)
		{
			Vector3D dif = finalNode->worldPosition - actualNode->worldPosition;
			return dif.x*dif.x + dif.y*dif.y + dif.z+dif.z;
		};
		break;
	case Heuristic::kManhatan:
		pHeuristicFoo = [](GraphNode* finalNode, GraphNode*actualNode)
		{
			Vector3D dif = finalNode->worldPosition - actualNode->worldPosition;
			return abs(dif.x) + abs(dif.y);
		};
		break;

	}
}

void CWalkerBase::InitNodePool()
{
	m_pathNodeStaticPool.resize(MAX_ITERATIONS);
}

PathNode * CWalkerBase::GetNode()
{
	if (m_nodePoolIndex == MAX_ITERATIONS)
	{
		m_nodePoolIndex = 0;
	}
	return &m_pathNodeStaticPool[m_nodePoolIndex++];
}

CWalkerBase::~CWalkerBase()
{
}
