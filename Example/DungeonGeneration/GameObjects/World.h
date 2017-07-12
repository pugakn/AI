#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"

#include "../FSM/Units/FSM.h"
#include "../FSM/Units/Faction.h"
#include "../FSM/Units/Armor.h"
#include "../FSM/Units/TerrainType.h"
#include "../FSM/Units/Type.h"
#include "../FSM/Units/WeaponType.h"

#include "../DungeonGeneration/DungeonMap.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>
#include "../DungeonGeneration/sfLineT.h"
#include <conio.h>
const sf::Uint32 winWidth = 1080;
const sf::Uint32 winHeight = 680;
class CWorld
{
private:
	const float UNIT_SCALE = 1;
	const float MOVE_AREA_X = 300;
	const float MOVE_AREA_Y = 150;
	const float CAM_VEL = 30;

	std::vector <std::shared_ptr<CGameObject>> m_ObjectList;

	std::vector<CFaction> m_factions;
	std::vector<CArmor> m_armors;
	std::vector<CTerrainType> m_terrainType;
	std::vector<CType> m_types;
	std::vector<CWeaponType> m_weaponTypes;


	std::vector<sf::RectangleShape> shapes;
	std::vector<sf::RectangleShape> m_tiles;
	std::vector<std::vector<sf::Vertex>> lines;
	std::vector<std::vector<sfLine>> corridors;

public:
	const int NUM_BLOCKS = 100;
	void Init();
	void InitMap();
	void Destroy();
	void Update(float delta, sf::RenderWindow&window);
	void Render(sf::RenderWindow &window);
	void CreateBoid(Vector3D position, float fRadius);
	void CreateObstacle(Vector3D position, float fRadius);
	CFaction GetFactionByID(unsigned short id);
	CArmor GetArmorByID(unsigned short id);
	CTerrainType GetTerrainTypenByID(unsigned short id);
	CType GetTypeByID(unsigned short id);
	CWeaponType GetWeaponTypeByID(unsigned short id);
	DungeonMap map;
	CFSM unitFSM;
	CFSM animFSM;

	void MoveUnit(float x, float y);
	CWorld();
	~CWorld();
};

