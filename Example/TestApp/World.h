#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"
#include "Obstacle.h"
class CWorld
{
private:
	std::vector <std::shared_ptr<CGameObject>> m_ObjectList;
	std::vector<std::shared_ptr<CObstacle>> m_pObstacleList;
public:
	void Init();
	void Destroy();
	void Update(float delta);
	void Render();
	void CreateBoid(Vector3D position, float fRadius);
	void CreateObstacle(Vector3D position, float fRadius);
	CWorld();
	~CWorld();
};

