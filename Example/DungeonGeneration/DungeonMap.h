#pragma once
#include <Vector2Di.h>
#include <vector>
#include <list>
#include "Utils.h"
#include "Triangle.h"
#include "FSM\State.h"
#include <memory>
#if VISUAL_DEBUG_MODE
#include <mutex>
#endif
struct DungeonHall
{
	std::vector<Vector2Di> points;
	float size;
};
struct DungeoBlock 
{
	Vector2Di size;
	//Center position
	Vector2Di position;
	std::vector<DungeoBlock*> graphConnections;
	//Vector3D Separation(float width, float height);
};
struct DungeonMapData
{
	int m_iSeed;
	int m_iNumBlocks;
	float m_fMinSeparation;
	float m_fSpawnRadius;
	Vector2Di m_initialPos;
	Vector2Di m_blockMinSize;
	Vector2Di m_blockMaxSize;
	//All blocks below this size will be removed after separation
	Vector2Di m_minValidSize;
	//Probability for remove a connection 0-100
	int m_iMinSpanningTreeProbability;


};
struct Tile
{
	int type;
	std::weak_ptr<CState> m_state;
};
class DungeonMap
{
private:
	DungeonMapData m_data;
	//Returns a random point on radius
	Vector2Di RandomPointOnRadius(Vector2Di pos, float radius);
	//Separate blocks with m_fMinSeparation
	void SeparateBlocks();
	//Remove blocks below m_minValidSize
	void RemoveInvalidBlocks();
	void DelaunayTriangulation();
	void RemoveRedundantConnections();
	void CreateGraphConnections();
	void CreateCorridors();
	void FillTiles();
public:
	const int TILE_SIZE = 8;
	int minX;
	int minY;
	int maxX;
	int maxY;
	int nTilesX;
	int nTilesY;
	std::vector<Tile> m_tiles;
#if VISUAL_DEBUG_MODE
	std::mutex m_mutex;
#endif
	std::vector<DungeoBlock> m_blocks;
	std::vector<DungeonHall> m_corridors;
	void GenerateMap(const DungeonMapData& data);
	std::list<Triangle> m_triangles;
	std::list<Edge> m_finalEdges;;

};

