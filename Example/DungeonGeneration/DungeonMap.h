#pragma once
#include <Vector3D.h>
#include <vector>
#include "Utils.h"
#if VISUAL_DEBUG_MODE
#include <mutex>
#endif
struct DungeoBlock 
{
	Vector3D size;
	//Center position
	Vector3D position;
	std::vector<DungeoBlock*> connections;
	//Vector3D Separation(float width, float height);
};
struct DungeonMapData
{
	int m_iSeed;
	int m_iNumBlocks;
	float m_fMinSeparation;
	float m_fSpawnRadius;
	Vector3D m_initialPos;
	Vector3D m_blockMinSize;
	Vector3D m_blockMaxSize;
	//All blocks below this size will be removed after separation
	Vector3D m_minValidSize;
	//Probability for removing a connection 
	float m_fMinSpanningTreeProbability;


};
class DungeonMap
{
private:
	DungeonMapData m_data;
	Vector3D RandomPointOnRadius(Vector3D pos, float radius);
	void SeparateBlocks();
	void RemoveInvalidBlocks();
	void DelaunayTriangulation();
	void RemoveRedundantConnections();
public:
#if VISUAL_DEBUG_MODE
	std::mutex m_mutex;
#endif
	std::vector<DungeoBlock> m_blocks;
	void GenerateMap(const DungeonMapData& data);

};

