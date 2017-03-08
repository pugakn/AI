#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"
#include "Obstacle.h"

#include "FSM.h"
#include "Faction.h"
#include "Armor.h"
#include "TerrainType.h"
#include "Type.h"
#include "WeaponType.h"

class CWorld
{
private:
	std::vector <std::shared_ptr<CGameObject>> m_ObjectList;
	std::vector <std::shared_ptr<CObstacle>> m_pObstacleList;

	std::vector<CFaction> m_factions;
	std::vector<CArmor> m_armors;
	std::vector<CTerrainType> m_terrainType;
	std::vector<CType> m_types;
	std::vector<CWeaponType> m_weaponTypes;


public:
	void Init();
	void Destroy();
	void Update(float delta);
	void Render();
	void CreateBoid(Vector3D position, float fRadius);
	void CreateObstacle(Vector3D position, float fRadius);
	CFaction GetFactionByID(unsigned short id);
	CArmor GetArmorByID(unsigned short id);
	CTerrainType GetTerrainTypenByID(unsigned short id);
	CType GetTypeByID(unsigned short id);
	CWeaponType GetWeaponTypeByID(unsigned short id);

	CWorld();
	~CWorld();
};

