#include "stdafx.h"
#include "DungeonMap.h"
#include <algorithm>
#include "Triangle.h"
#include "Edge.h"
#include "Vector3D.h"

Vector2Di DungeonMap::RandomPointOnRadius(Vector2Di pos, float radius)
{
	float angle = FloatRand(0, M_2PI);
	float randRadius = FloatRand(0.f, radius);
	return Vector2Di(cosf(angle)* randRadius + pos.x, sinf(angle)*randRadius + pos.y);
}

void DungeonMap::SeparateBlocks()
{
	bool finished = false;
	while (!finished)
	{
		finished = true;
		for (auto &block : m_blocks)
		{
			Vector2Di forces(0, 0);
			for (auto &it : m_blocks)
			{
				Vector2Di separation = block.position - it.position;
				int blockLeft = block.position.x - block.size.x /2 - m_data.m_fMinSeparation ;
				int blockRight = block.position.x + block.size.x / 2 + m_data.m_fMinSeparation ;
				int blockTop = block.position.y + block.size.y / 2 + m_data.m_fMinSeparation;
				int blockBottom = block.position.y - block.size.y / 2 - m_data.m_fMinSeparation;

				int itLeft =   it.position.x -  it.size.x / 2;
				int itRight =  it.position.x + it.size.x / 2;
				int itTop =    it.position.y +   it.size.y / 2;
				int itBottom = it.position.y -it.size.y / 2;
				//If two blocks intersect, add separation force
				if (blockLeft < itRight && blockRight > itLeft &&
					blockTop > itBottom && blockBottom < itTop && Magnitude(separation) != 0)
				{
					forces +=  GetDirection(separation);
					finished = false;
				}
			}
			block.position += Vector2Di(forces.x,forces.y);
		}
	}
}

void DungeonMap::RemoveInvalidBlocks()
{
	for (size_t i = 0; i < m_blocks.size(); ++i)
	{
		if (m_blocks[i].size.x < m_data.m_minValidSize.x ||
			m_blocks[i].size.y < m_data.m_minValidSize.y  )
		{
			m_blocks.erase(m_blocks.begin() + i);
			i--;
		}
	}
}

void DungeonMap::DelaunayTriangulation()
{
	
	minX = m_blocks[0].position.x - m_blocks[0].size.x / 2;
	minY = m_blocks[0].position.y - m_blocks[0].size.y / 2;
	maxX = m_blocks[0].position.x + m_blocks[0].size.x / 2;
	maxY = m_blocks[0].position.y + m_blocks[0].size.y /2 ;
	//Get min and max points
	for (std::size_t i = 0; i < m_blocks.size(); ++i)
	{
		int newMinX = m_blocks[i].position.x - m_blocks[i].size.x /2 ;
		int newMinY = m_blocks[i].position.y - m_blocks[i].size.y /2 ;
		int newMaxX = m_blocks[i].position.x + m_blocks[i].size.x /2 ;
		int newMaxY = m_blocks[i].position.y + m_blocks[i].size.y /2 ;
		if (newMinX < minX) minX = newMinX -1;
		if (newMinY < minY) minY = newMinY -1;
		if (newMaxX > maxX) maxX = newMaxX +1;
		if (newMaxY > maxY) maxY = newMaxY +1;
	}
	//Create super triangles containing all other points
	Vector2Di p1(minX, minY);
	Vector2Di p2(minX, maxY);
	Vector2Di p3(maxX, minY);
	Triangle superTriangle = Triangle( p1, p2, p3 );
	Vector2Di p4(maxX, minY);
	Vector2Di p5(maxX, maxY);
	Vector2Di p6(minX, maxY);
	Triangle superTriangle2 = Triangle{ p4, p5, p6 };
	//Insert super triangles into triangulation list
	m_triangles.push_back(superTriangle);
	m_triangles.push_back(superTriangle2);
	//Iterate for each point in the point list
	for (auto &point : m_blocks)
	{
		std::list<Edge> polygon;//Contains the edges of the convex poligon that results from removing invalid triangles
		std::list<Edge> invalidEdges;//Contains the edges shared by other triangles on badTriangles
		//Search for invalid triangles
		for (auto triangle = m_triangles.begin(); triangle != m_triangles.end();)
		{
			//Remove from the triangulation list all bad triangles and add its edges to the polygon list
			if (triangle->IsPointOnCircumCircle(point.position))
			{
				for (auto &edge : triangle->edges)
				{
					polygon.push_back(edge);
				}
				triangle = m_triangles.erase(triangle);
			}
			else
				triangle++;
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
	for (auto triangle = m_triangles.begin(); triangle != m_triangles.end();)
	{
		if (triangle->p1.p == p1 || triangle->p1.p == p2 || triangle->p1.p == p3 || triangle->p1.p == p4 || triangle->p1.p == p5 || triangle->p1.p == p6 ||
			triangle->p2.p == p1 || triangle->p2.p == p2 || triangle->p2.p == p3 || triangle->p2.p == p4 || triangle->p2.p == p5 || triangle->p2.p == p6 ||
			triangle->p3.p == p1 || triangle->p3.p == p2 || triangle->p3.p == p3 || triangle->p3.p == p4 || triangle->p3.p == p5 || triangle->p3.p == p6)
		{
			triangle = m_triangles.erase(triangle);
		}
		else
			triangle++;
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
					if ((triangle.edges[i].p1.p == edge.p1.p && triangle.edges[i].p2.p == edge2.p1.p)
						|| (triangle.edges[i].p2.p == edge.p1.p && triangle.edges[i].p1.p == edge2.p1.p)
						|| (triangle.edges[i].p1.p == edge.p2.p && triangle.edges[i].p2.p == edge2.p2.p)
						|| (triangle.edges[i].p2.p == edge.p2.p && triangle.edges[i].p1.p == edge2.p2.p)
						|| (triangle.edges[i].p1.p == edge.p1.p && triangle.edges[i].p2.p == edge2.p2.p)
						|| (triangle.edges[i].p2.p == edge.p1.p && triangle.edges[i].p1.p == edge2.p2.p)
						|| (triangle.edges[i].p1.p == edge.p2.p && triangle.edges[i].p2.p == edge2.p1.p)
						|| (triangle.edges[i].p2.p == edge.p2.p && triangle.edges[i].p1.p == edge2.p1.p))
					{
						//Remove edge based on m_iMinSpanningTreeProbability  
						if (rand() % 100 < m_data.m_iMinSpanningTreeProbability)
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
	std::vector<DungeoBlock*> ignoreList;
	for (auto &block : m_blocks)
	{
		ignoreList.push_back(&block);
		for (auto &con : block.graphConnections)
		{
			bool corridorLoop = true;
			for (auto ignore : ignoreList)
			{
				if (con == ignore)
					corridorLoop = false;
			}
			if (!corridorLoop)
				continue;
			m_corridors.push_back(DungeonHall());
			Vector2Di tmp;
			Vector2Di bigLine = con ->position - Vector2Di(block.position.x,con->position.y);
			Vector2Di shortLine = Vector2Di(block.position.x, con->position.y) - block.position;
			if (Magnitude(shortLine) > Magnitude(bigLine))
			{
				Vector2Di temp = shortLine;
				shortLine = bigLine;
				bigLine = temp;
			}
			Vector2Di startPoint;
			Vector2Di midPoint;
			Vector2Di finalPoint;
			startPoint = block.position;
			midPoint = startPoint + shortLine;
			finalPoint = midPoint + bigLine;
			//
			Vector2Di blockMidSize = block.size /2;
			Vector2Di blockMinCorner = block.position - blockMidSize;
			Vector2Di blockMaxCorner = block.position + blockMidSize;
			if (midPoint.x > blockMinCorner.x && midPoint.x < blockMaxCorner.x
				&& midPoint.y > blockMinCorner.y && midPoint.y < blockMaxCorner.y)
			{
				if (finalPoint.y > midPoint.y)
				{
					midPoint += Vector2Di( 0, blockMidSize.y );
					startPoint = midPoint;
				}
				else if (finalPoint.y < midPoint.y)
				{
					midPoint += Vector2Di(0, -blockMidSize.y );
					startPoint = midPoint;
				}
				else if (finalPoint.x > midPoint.x)
				{
					midPoint += Vector2Di(blockMidSize.x,0);
					startPoint = midPoint;
				}
				else if (finalPoint.x < midPoint.x)
				{
					midPoint += Vector2Di(-blockMidSize.x,0);
					startPoint = midPoint;
				}
			}
			
			if (midPoint.y > startPoint.y)
			{
				startPoint += Vector2Di(0, blockMidSize.y);
			}
			else if (midPoint.y < startPoint.y)
			{
				startPoint += Vector2Di(0, -blockMidSize.y);
			}
			else if (midPoint.x > startPoint.x)
			{
				startPoint += Vector2Di(blockMidSize.x, 0);
			}
			else if (midPoint.x < startPoint.x)
			{
				startPoint += Vector2Di(-blockMidSize.x, 0);
			}
			
			Vector2Di conMidSize = con->size /2;
			if (finalPoint.y > midPoint.y)
			{
				finalPoint += Vector2Di(0, -conMidSize.y);
			}
			else if (finalPoint.y < midPoint.y)
			{
				finalPoint += Vector2Di(0, conMidSize.y);
			}
			else if (finalPoint.x > midPoint.x)
			{
				finalPoint += Vector2Di(-conMidSize.x, 0);
			}
			else if (finalPoint.x < midPoint.x)
			{
				finalPoint += Vector2Di(conMidSize.x, 0);
			}

			//============== Switch invalid connections ================
			for (auto &badBlock : m_blocks)
			{
				Vector2Di badBlockMidSize = badBlock.size /2;
				int blockLeft = badBlock.position.x - badBlockMidSize.x;
				int blockRight = badBlock.position.x + badBlockMidSize.x;
				int blockTop = badBlock.position.y + badBlockMidSize.y;
				int blockBottom = badBlock.position.y - badBlockMidSize.y;


				if (midPoint.x > blockLeft && midPoint.x < blockRight && midPoint.y > blockBottom && midPoint.y < blockTop)
				//if ((midPoint.x > blockLeft && midPoint.x < blockRight && midPoint.y < blockTop && startPoint.y > blockBottom )
				//	|| (midPoint.x > blockLeft && midPoint.x < blockRight && midPoint.y > blockBottom && startPoint.y < blockTop)
				//	|| (midPoint.x > blockLeft && midPoint.x < blockRight && midPoint.y > blockBottom && midPoint.y < blockTop))
				{
					if (midPoint == startPoint || midPoint == finalPoint)
						continue;
					startPoint = block.position;
					midPoint = startPoint + bigLine;
					finalPoint = midPoint + shortLine;

					Vector2Di conMinCorner = con->position - conMidSize;
					Vector2Di conMaxCorner = con->position + conMidSize;
					if (midPoint.x > conMinCorner.x && midPoint.x < conMaxCorner.x
						&& midPoint.y > conMinCorner.y && midPoint.y < conMaxCorner.y)
					{
						if (finalPoint.y == midPoint.y)
						{
							if (block.position.y > con->position.y)
							{
								midPoint += Vector2Di(0, conMidSize.y);
								finalPoint = midPoint;
							}
							else
							{
								midPoint += Vector2Di(0, -conMidSize.y);
								finalPoint = midPoint;
							}
						}
						else
						{
							if (block.position.x > con->position.x)
							{
								midPoint += Vector2Di(conMidSize.x, 0);
								finalPoint = midPoint;
							}
							else
							{
								midPoint += Vector2Di(-conMidSize.x, 0);
								finalPoint = midPoint;
							}
						}
					}
					if (midPoint.y > startPoint.y)
					{
						startPoint += Vector2Di(0, blockMidSize.y);
					}
					else if (midPoint.y < startPoint.y)
					{
						startPoint += Vector2Di(0, -blockMidSize.y);
					}
					else if (midPoint.x > startPoint.x)
					{
						startPoint += Vector2Di(blockMidSize.x, 0);
					}
					else if (midPoint.x < startPoint.x)
					{
						startPoint += Vector2Di(-blockMidSize.x, 0);
					}


					if (finalPoint.y > midPoint.y)
					{
						finalPoint += Vector2Di(0, -conMidSize.y);
					}
					else if (finalPoint.y < midPoint.y)
					{
						finalPoint += Vector2Di(0, conMidSize.y);
					}
					else if (finalPoint.x > midPoint.x)
					{
						finalPoint += Vector2Di(-conMidSize.x, 0);
					}
					else if (finalPoint.x < midPoint.x)
					{
						finalPoint += Vector2Di(conMidSize.x, 0);
					}

				}
			}
			//======================================
			m_corridors.back().points.push_back(startPoint);
			m_corridors.back().points.push_back(midPoint);
			m_corridors.back().points.push_back(finalPoint);


		}
	}

}

void DungeonMap::FillTiles()
{
	nTilesX = (maxX - minX) / TILE_SIZE;
	nTilesY = (maxY - minY) / TILE_SIZE;
	m_tiles.resize(nTilesX * nTilesY);

	int y = 0;
	int x = 0;
	for (size_t i = 0 ; i < m_tiles.size(); i++)
	{

		m_tiles[i].type = 0;
		m_tiles[i].xIndex = x;
		m_tiles[i].yIndex = y;
		x++;
		if (x > nTilesX - 1)
		{
			x = 0;
			y++;
		}
	}

	for (size_t i = 0; i < nTilesY; i++)
	{
		int TileMinX = minX;
		int TileMinY = minY + i * TILE_SIZE;
		int TileMAxX = TileMinX + TILE_SIZE;
		int TileMAxY = TileMinY + TILE_SIZE;
		for (size_t j = 0; j < nTilesX; j++)
		{
			for (auto & block : m_blocks)
			{
				auto minCornerPos = block.position - block.size / 2;
				auto mmaxCornerPos = block.position + block.size / 2;
				if (minCornerPos.x <= TileMinX && mmaxCornerPos.x >= TileMAxX)
					if (minCornerPos.y <= TileMinY && mmaxCornerPos.y >= TileMAxY)
					{
						m_tiles[i * nTilesX + j].type = 1;
						break;
					}
			}
			//Avanzar al siguiente tile
			TileMinX = TileMAxX;
			TileMAxX = TileMinX + TILE_SIZE;
		}
	}
	//nTilesX = nTilesX + TILE_SIZE;//debug

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
		m_blocks[i].size = Vector2Di(FloatRand(m_data.m_blockMinSize.x,m_data.m_blockMaxSize.x),
			FloatRand(m_data.m_blockMinSize.y, m_data.m_blockMaxSize.y));
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
	FillTiles();
#if VISUAL_DEBUG_MODE
	m_mutex.unlock();
#endif
}
