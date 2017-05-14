#include "stdafx.h"
#include "DungeonMap.h"

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
				Vector3D separation = it.position - block.position;
				if (((abs(separation.x) < block.size.x / 2.f + m_data.m_fMinSeparation + it.size.x / 2.f)
					&& (abs(separation.y) < block.size.y / 2.f + m_data.m_fMinSeparation + it.size.y / 2.f))
					&& Magnitude(separation) != 0)
				{
					forces += Normalize(separation) * (block.size.x / Magnitude(separation) - 1);
					finished = false;
				}
			}
			block.position += forces;
		}
	}
}

void DungeonMap::RemoveInvalidBlocks()
{
#if VISUAL_DEBUG_MODE
	m_mutex.lock();
#endif
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
#if VISUAL_DEBUG_MODE
	m_mutex.unlock();
#endif
}

void DungeonMap::DelaunayTriangulation()
{
}

void DungeonMap::RemoveRedundantConnections()
{
}

void DungeonMap::GenerateMap(const DungeonMapData& data)
{
	m_data = data;
	m_blocks.resize(m_data.m_iNumBlocks);

	srand(m_data.m_iSeed);
	for (size_t i = 0; i < m_data.m_iNumBlocks; i++)
	{
		m_blocks[i].position = RandomPointOnRadius(m_data.m_initialPos, m_data.m_fSpawnRadius);
		m_blocks[i].size = Vector3D(FloatRand(m_data.m_blockMinSize.x,m_data.m_blockMaxSize.x), 
			FloatRand(m_data.m_blockMinSize.y, m_data.m_blockMaxSize.y), 
			FloatRand(m_data.m_blockMinSize.z, m_data.m_blockMaxSize.z));
	}
	SeparateBlocks();
	RemoveInvalidBlocks();
	DelaunayTriangulation();
	RemoveRedundantConnections();
}
