#pragma once
#include <Vector3D.h>
#include <vector>
#include <list>
#include "Utils.h"
#include "Triangle.h"
#if VISUAL_DEBUG_MODE
#include <mutex>
#endif
struct DungeonHall
{
	std::vector<Vector3D> points;
};
struct DungeoBlock 
{
	Vector3D size;
	//Center position
	Vector3D position;
	std::vector<DungeoBlock*> graphConnections;
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
	//Probability for remove a connection 0-100
	int m_iMinSpanningTreeProbability;


};
class DungeonMap
{
private:
	DungeonMapData m_data;
	//Returns a random point on radius
	Vector3D RandomPointOnRadius(Vector3D pos, float radius);
	//Separate blocks with m_fMinSeparation
	void SeparateBlocks();
	//Remove blocks below m_minValidSize
	void RemoveInvalidBlocks();
	void DelaunayTriangulation();
	void RemoveRedundantConnections();
	void CreateGraphConnections();
	void CreateCorridors();
public:
#if VISUAL_DEBUG_MODE
	std::mutex m_mutex;
#endif
	std::vector<DungeoBlock> m_blocks;
	std::vector<DungeonHall> m_corridors;
	void GenerateMap(const DungeonMapData& data);
	std::list<Triangle> m_triangles;
	std::list<Edge> m_finalEdges;;

};

