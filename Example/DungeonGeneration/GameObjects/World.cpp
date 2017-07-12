#include "World.h"
#include "Boid.h"
#include <time.h>
#include <memory>
#include <iostream>
#include "../Unit.h"
void CWorld::Init()
{
	srand(time(NULL));

	CType champion;
	champion.m_uId = 0;
	m_types.push_back(champion);

	m_ObjectList.push_back(std::make_shared<CUnit>());
	std::dynamic_pointer_cast<CUnit>(m_ObjectList.back())->SetAnimation("champion");
	m_ObjectList.back()->Init();
	unitFSM.Attach(m_ObjectList.back());


	unitFSM.Init(this, CFSM::FSM_TYPE::UNIT);
	animFSM.Init(this, CFSM::FSM_TYPE::ANIM);
}

void CWorld::InitMap()
{
	DungeonMapData tmpData;
	tmpData.m_blockMinSize = Vector2Di(5, 5);
	tmpData.m_blockMaxSize = Vector2Di(100, 100);
	tmpData.m_iMinSpanningTreeProbability = 85;
	tmpData.m_fSpawnRadius = 30;
	tmpData.m_initialPos = Vector2Di(512, 768 / 2.f);
	tmpData.m_iNumBlocks = NUM_BLOCKS;
	tmpData.m_iSeed = 666366;
	tmpData.m_minValidSize = Vector2Di(50, 50);
	tmpData.m_fMinSeparation = 3.f;
	map.GenerateMap(tmpData);
	shapes.resize(NUM_BLOCKS);
	for (size_t i = 0; i < shapes.size(); ++i)
	{
		shapes[i].setFillColor(sf::Color::Green);
		shapes[i].setOutlineColor(sf::Color::Red);
		shapes[i].setOutlineThickness(1);
	}
	for (int i = 0; i < map.m_blocks.size(); ++i)
	{
		shapes[i].setSize(sf::Vector2f(map.m_blocks[i].size.x, map.m_blocks[i].size.y) * UNIT_SCALE);
		shapes[i].setPosition(sf::Vector2f(map.m_blocks[i].position.x, map.m_blocks[i].position.y)* UNIT_SCALE);
		shapes[i].setOrigin(shapes[i].getSize() / 2.f);
	}
	shapes.resize(map.m_blocks.size());
	static bool first = true;
	if (first) {
		if (map.m_blocks[0].graphConnections.size() != 0) {
			for (auto &block : map.m_blocks)
			{
				std::vector<sf::Vertex> tmp;
				for (auto &con : block.graphConnections)
				{
					sf::Vertex v1(sf::Vector2f(block.position.x, block.position.y)* UNIT_SCALE);
					sf::Vertex v2(sf::Vector2f(con->position.x, con->position.y)* UNIT_SCALE);
					tmp.push_back(v1);
					tmp.push_back(v2);
				}
				lines.push_back(tmp);
			}
			first = false;
		}

		if (map.m_corridors.size() != 0) {
			for (auto &corridor : map.m_corridors)
			{
				std::vector<sfLine> tmp;
				sf::Vector2f v1(corridor.points[0].x, corridor.points[0].y);
				sf::Vector2f v2(corridor.points[1].x, corridor.points[1].y);
				v1 *= UNIT_SCALE;
				v2 *= UNIT_SCALE;
				tmp.push_back(sfLine(v1, v2, 3 * UNIT_SCALE));
				tmp.back().SetColor(sf::Color::Red);
				v1 = sf::Vector2f(corridor.points[1].x, corridor.points[1].y);
				v2 = sf::Vector2f(corridor.points[2].x, corridor.points[2].y);
				v1 *= UNIT_SCALE;
				v2 *= UNIT_SCALE;
				tmp.push_back(sfLine(v1, v2, 3 * UNIT_SCALE));
				tmp.back().SetColor(sf::Color::Red);
				corridors.push_back(tmp);
			}
			first = false;
		}
	}
	m_tiles.resize(map.m_tiles.size());
	for (size_t i = 0; i < m_tiles.size(); ++i)
	{
		m_tiles[i].setSize(sf::Vector2f(map.TILE_SIZE,map.TILE_SIZE));
		static int y = 0;
		y = i % map.TILE_SIZE;
		m_tiles[i].setPosition(sf::Vector2f());
		if (map.m_tiles[i] == 1)
			m_tiles[i].setFillColor(sf::Color::Green);
		m_tiles[i].setOutlineColor(sf::Color::Red);
		m_tiles[i].setOutlineThickness(1);
	}
}

void CWorld::Destroy()
{
	for (auto &item : m_ObjectList)
		item->Destroy();
}

void CWorld::Update(float delta, sf::RenderWindow& window)
{
	for (auto &item : m_ObjectList)
		item->Update(delta);

	auto pos = sf::Mouse::getPosition(window);

	if ((winWidth - pos.x)< MOVE_AREA_X)
	{
		float factor = (MOVE_AREA_X - winWidth + pos.x) / MOVE_AREA_X;
		float move = CAM_VEL * factor;
		sf::View biew = window.getView();
		biew.move(move, 0);
		window.setView(biew);
	}
	if ((pos.x)< MOVE_AREA_X)
	{
		float factor = (MOVE_AREA_X - pos.x) / MOVE_AREA_X;
		sf::View biew = window.getView();
		float move = CAM_VEL * factor;
		biew.move(-move, 0);
		window.setView(biew);
	}
	if ((winHeight - pos.y)< MOVE_AREA_Y)
	{
		float factor = (MOVE_AREA_Y - winHeight + pos.y) / MOVE_AREA_Y;
		sf::View biew = window.getView();
		float move = CAM_VEL * factor;
		biew.move(0, move);
		window.setView(biew);
	}
	if ((pos.y)< MOVE_AREA_Y)
	{
		float factor = (MOVE_AREA_Y - pos.y) / MOVE_AREA_Y;
		sf::View biew = window.getView();
		float move = CAM_VEL * factor;
		biew.move(0, -move);
		window.setView(biew);
	}
}

void CWorld::Render(sf::RenderWindow &window)
{
	for (auto &item : m_ObjectList)
		item->Render();


	sf::RenderStates rs;
	if (map.m_corridors.size() != 0) {
		for (int i = 0; i < corridors.size(); i++)
		{
			for (int j = 0; j < 2; j++)
			{
				corridors[i][j].draw(window, rs);
			}
		}
	}
	for (auto &shape : shapes)
	{
		window.draw(shape);
	}
	for (auto &shape : m_tiles)
	{
		window.draw(shape);
	}
}

void CWorld::CreateBoid(Vector3D position, float fRadius)
{
	m_ObjectList.push_back(std::make_shared<CBoid>());
	m_ObjectList.back()->Init();
	m_ObjectList.back()->SetPosition(position);
	(dynamic_cast<CBoid*>(m_ObjectList.back().get()))->SetRadius(fRadius);
}

//Obtener las propiedades de una facción por id
CFaction CWorld::GetFactionByID(unsigned short id)
{
	for (auto &it : m_factions)
		if (it.m_uId == id)
			return it;
}
//Obtener las propiedades de una armadura por id
CArmor CWorld::GetArmorByID(unsigned short id)
{
	for (auto &it : m_armors)
		if (it.m_uId == id)
			return it;
}
//Obtener las propiedades de un terreno por id
CTerrainType CWorld::GetTerrainTypenByID(unsigned short id)
{
	for (auto &it : m_terrainType)
		if (it.m_uId == id)
			return it;
}
//Obtener las propiedades de un tipo de unidad por id
CType CWorld::GetTypeByID(unsigned short id)
{
	for (auto &it : m_types)
		if (it.m_uId == id)
			return it;
}
//Obtener las propiedades de un tipo de arma por id
CWeaponType CWorld::GetWeaponTypeByID(unsigned short id)
{
	for (auto &it : m_weaponTypes)
		if (it.m_uId == id)
			return it;
}

void CWorld::MoveUnit(float x, float y)
{
	std::dynamic_pointer_cast<CUnit>(m_ObjectList.back())->m_targetPos = Vector3D(x, y, 0.0);
	unitFSM.SetState(m_ObjectList.back(), CFSM::MOVE_TO);
	animFSM.SetState(m_ObjectList.back(), CFSM::MOVE_TO);
}

CWorld::CWorld()
{
}


CWorld::~CWorld()
{
}

