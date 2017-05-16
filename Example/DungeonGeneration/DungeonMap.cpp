#include "stdafx.h"
#include "DungeonMap.h"
#include <algorithm>
#include "Triangle.h"
#include "Edge.h"

Vector3D DungeonMap::RandomPointOnRadius(Vector3D pos, float radius)
{
	float angle = FloatRand(0, M_2PI);
	float randRadius = FloatRand(0.f, radius);
	return Vector3D(cosf(angle)* randRadius + pos.x, sinf(angle)*randRadius + pos.y, 0.f);
}

void DungeonMap::SeparateBlocks()
{
	bool finished = false;
	while (!finished)
	{
		finished = true;
		for (auto &block : m_blocks)
		{
			Vector3D forces(0, 0, 0);
			for (auto &it : m_blocks)
			{

				Vector3D separation = block.position- it.position;
				float blockLeft = block.position.x - block.size.x / 2.f - m_data.m_fMinSeparation ;
				float blockRight = block.position.x + block.size.x / 2.f + m_data.m_fMinSeparation ;
				float blockTop = block.position.y + block.size.y / 2.f + m_data.m_fMinSeparation;
				float blockBottom = block.position.y - block.size.y / 2.f - m_data.m_fMinSeparation;

				float itLeft =   it.position.x -  it.size.x / 2.f ;
				float itRight =  it.position.x + it.size.x / 2.f ;
				float itTop =    it.position.y +   it.size.y / 2.f ;
				float itBottom = it.position.y -it.size.y / 2.f ;
				//If two blocks intersect, add separation force
				if (blockLeft < itRight && blockRight > itLeft &&
					blockTop > itBottom && blockBottom < itTop && Magnitude(separation) != 0)
				{
					forces +=  Normalize(separation);
					finished = false;
				}
			}
			block.position += forces;
		}
	}
}

void DungeonMap::RemoveInvalidBlocks()
{
	for (size_t i = 0; i < m_blocks.size(); ++i)
	{
		if (m_blocks[i].size.x < m_data.m_minValidSize.x ||
			m_blocks[i].size.y < m_data.m_minValidSize.y || 
			m_blocks[i].size.z < m_data.m_minValidSize.z)
		{
			m_blocks.erase(m_blocks.begin() + i);
			i--;
		}
	}
}

void DungeonMap::DelaunayTriangulation()
{
	
	float minX = m_blocks[0].position.x - m_blocks[0].size.x / 2.f;
	float minY = m_blocks[0].position.y - m_blocks[0].size.y / 2.f;
	float maxX = m_blocks[0].position.x + m_blocks[0].size.x / 2.f;
	float maxY = m_blocks[0].position.y + m_blocks[0].size.y / 2.f;
	//Get min and max points
	for (std::size_t i = 0; i < m_blocks.size(); ++i)
	{
		float newMinX = m_blocks[i].position.x - m_blocks[i].size.x / 2.f;
		float newMinY = m_blocks[i].position.y - m_blocks[i].size.y / 2.f;
		float newMaxX = m_blocks[i].position.x + m_blocks[i].size.x / 2.f;
		float newMaxY = m_blocks[i].position.y + m_blocks[i].size.y / 2.f;
		if (newMinX < minX) minX = newMinX;
		if (newMinY < minY) minY = newMinY;
		if (newMaxX > maxX) maxX = newMaxX;
		if (newMaxY > maxY) maxY = newMaxY;
	}
	//Create super triangles containing all other points
	Vector3D p1(minX, minY, 0);
	Vector3D p2(minX, maxY, 0);
	Vector3D p3(maxX, minY, 0);
	Triangle superTriangle = Triangle( p1, p2, p3 );
	Vector3D p4(maxX, minY, 0);
	Vector3D p5(maxX, maxY, 0);
	Vector3D p6(minX, maxY, 0);
	Triangle superTriangle2 = Triangle{ p4, p5, p6 };
	//Insert super triangles into triangulation list
	m_triangles.push_back(superTriangle);
	m_triangles.push_back(superTriangle2);
	//Iterate for each point in the point list
	for (auto &point : m_blocks)
	{
		std::list<Triangle> badTriangles;//Contains all triangles with a point inside its circumcircle
		std::list<Edge> polygon;//Contains the edges of the convex poligon that results from removing invalid triangles
		std::list<Edge> invalidEdges;//Contains the edges shared by other triangles on badTriangles
		//Search for invalid triangles
		for (auto &triangle : m_triangles)
		{
			if (triangle.IsPointOnCircumCircle(point.position))
			{
				badTriangles.push_back(triangle);
			}
		}
		//Remove from the triangulation list all bad triangles and add its edges to the polygon list
		for (auto &triangle : badTriangles)
		{
			m_triangles.remove_if([triangle](Triangle other) { return triangle == other; });
			for (auto &edge : triangle.edges)
			{
				polygon.push_back(edge);
			}
		}
		//Search for invalid edges on the convex polygon
		for (auto &edge1 : polygon)
		{
			for (auto &edge2 : polygon)
			{
				if (&edge1 == &edge2)
					continue;
				if (edge1 == edge2)
				{
					invalidEdges.push_back(edge1);
					invalidEdges.push_back(edge2);
				}
			}
		}
		//Remove all invalid edges from Polygon
		for (auto &edge : invalidEdges)
		{
			polygon.remove_if([edge](Edge other) { return edge == other; });
		}
		//Create the new triangles from the actual point to all vertex on the convex polygon
		for (auto &edge : polygon)
		{
			m_triangles.push_back(Triangle(edge.p1,edge.p2,GraphPoint(point.position,&point)));
		}
	}
	//Remove conections to the super triangles
	bool finding = true;
	while (finding)
	{
		finding = false;
		for (auto &triangle : m_triangles)
		{
			if (triangle.p1.p == p1 || triangle.p1.p == p2 || triangle.p1.p == p3 || triangle.p1.p == p4 || triangle.p1.p == p5 || triangle.p1.p == p6 ||
				triangle.p2.p == p1 || triangle.p2.p == p2 || triangle.p2.p == p3 || triangle.p2.p == p4 || triangle.p2.p == p5 || triangle.p2.p == p6 ||
				triangle.p3.p == p1 || triangle.p3.p == p2 || triangle.p3.p == p3 || triangle.p3.p == p4 || triangle.p3.p == p5 || triangle.p3.p == p6)
			{
				m_triangles.remove_if([triangle](Triangle other) { return triangle == other; });
				finding = true;
				break;
			}
		}
	}
}

void DungeonMap::RemoveRedundantConnections()
{
	//Use minimum spanning tree to remove redundant connections 
	//and add the resultant edges to m_finalEdges
	for (auto &triangle : m_triangles)
	{
		for (size_t i = 0;i<triangle.edges.size();++i)
		{
			bool EdgeOk = true;
			for (auto &edge : m_finalEdges)
			{
				//Search for repeated edges
				if (triangle.edges[i] == edge)
				{
					EdgeOk = false;
					break;
				}
				for (auto &edge2 : m_finalEdges)
				{
					//Search for edges that form a cycle
					if ((triangle.edges[i].p1.p == edge.p1.p && triangle.edges[i].p2.p == edge2.p2.p)
						|| (triangle.edges[i].p2.p == edge.p1.p && triangle.edges[i].p1.p == edge2.p2.p))
					{
						//Remove edge based on m_iMinSpanningTreeProbability  
						if (rand() % 101 < m_data.m_iMinSpanningTreeProbability)
						{
							EdgeOk = false;
						}
						break;
					}
				}
			}
			//add the edge if it doesnt form a cycle
			if (EdgeOk)
				m_finalEdges.push_back(triangle.edges[i]);
		}
	}
}

void DungeonMap::CreateGraphConnections()
{
	for (auto &edge : m_finalEdges)
	{
		edge.p1.pGraphNode->graphConnections.push_back(edge.p2.pGraphNode);
		edge.p2.pGraphNode->graphConnections.push_back(edge.p1.pGraphNode);
	}

}

void DungeonMap::CreateCorridors()
{
	for (auto &block : m_blocks)
	{
		for (auto &con : block.graphConnections)
		{
			m_corridors.push_back(DungeonHall());
			Vector3D tmp;
			tmp = Vector3D(block.position);
			m_corridors.back().points.push_back(tmp);
			tmp = Vector3D(block.position.x, std::max(block.position.y,con->position.y),0);
			m_corridors.back().points.push_back(tmp);
			tmp = Vector3D(con->position);
			m_corridors.back().points.push_back(tmp);
		}
	}
}

void DungeonMap::GenerateMap(const DungeonMapData& data)
{
	m_data = data;
	m_blocks.resize(m_data.m_iNumBlocks);

	srand(m_data.m_iSeed);
	//Initialize blocks with random position and size
	for (size_t i = 0; i < m_data.m_iNumBlocks; i++)
	{
		m_blocks[i].position = RandomPointOnRadius(m_data.m_initialPos, m_data.m_fSpawnRadius);
		m_blocks[i].size = Vector3D(FloatRand(m_data.m_blockMinSize.x,m_data.m_blockMaxSize.x), 
			FloatRand(m_data.m_blockMinSize.y, m_data.m_blockMaxSize.y), 
			FloatRand(m_data.m_blockMinSize.z, m_data.m_blockMaxSize.z));
	}
	SeparateBlocks();
#if VISUAL_DEBUG_MODE
	m_mutex.lock();
#endif
	RemoveInvalidBlocks();
	DelaunayTriangulation();
	RemoveRedundantConnections();
	CreateGraphConnections();
	CreateCorridors();
#if VISUAL_DEBUG_MODE
	m_mutex.unlock();
#endif
}
