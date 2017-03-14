#include "World.h"
#include "Boid.h"
#include <time.h>
#include <memory>

void CWorld::Init()
{
	srand(time(NULL));
	//std::shared_ptr<std::vector<std::shared_ptr<CObstacle>>> obstaclePointer(&m_pObstacleList);
	///////////////////////////////////////////////////////
	//BOIDS//////////////////////////////////////////
	//Inicializar aqui los BOIDS
	///////////////////////////////////////////////////////


	//CreateBoid(Vector3D(0.5, 0, 0), 0.08f);
	//std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->SetObstacleList(&m_pObstacleList);
	//std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->SetWorldBoidsVector(&m_ObjectList);
	//std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kObstacleAvoidance);
	////std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kFollowPathArrive);
	////std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kFlocking);

	CreateBoid(Vector3D(0, 0, 0), 0.08f);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->SetObstacleList(&m_pObstacleList);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->SetWorldBoidsVector(&m_ObjectList);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kObstacleAvoidance);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kWander);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kFlocking);

	CreateBoid(Vector3D(0.3, 0, 0), 0.08f);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->SetObstacleList(&m_pObstacleList);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->SetWorldBoidsVector(&m_ObjectList);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kObstacleAvoidance);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kWander);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kFlocking);
	CreateBoid(Vector3D(0.3, 0, 0), 0.08f);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->SetObstacleList(&m_pObstacleList);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->SetWorldBoidsVector(&m_ObjectList);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kObstacleAvoidance);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kWander);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kFlocking);
	CreateBoid(Vector3D(0.3, 0, 0), 0.08f);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->SetObstacleList(&m_pObstacleList);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->SetWorldBoidsVector(&m_ObjectList);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kObstacleAvoidance);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kWander);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kFlocking);
	CreateBoid(Vector3D(0.3, 0, 0), 0.08f);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->SetObstacleList(&m_pObstacleList);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->SetWorldBoidsVector(&m_ObjectList);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kObstacleAvoidance);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kWander);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kFlocking);

	CreateBoid(Vector3D(0.4, 0, 0), 0.08f);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->SetObstacleList(&m_pObstacleList);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->SetWorldBoidsVector(&m_ObjectList);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->SetLider(true);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kObstacleAvoidance);
	//std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kWander2);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kFollowPathLoop);
	//std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kFollowTheLider);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//OBSTACULOS///////////////////////////////////////////
	//Inicializar aqui los obstaculos 
	///////////////////////////////////////////////////////
	//m_pObstacleList.push_back(std::make_shared<CObstacle>());
	//m_pObstacleList.back()->SetPosition(Vector3D(0, 0.01, 0));
	//m_pObstacleList.back()->SetRadius(0.08f);

	///////////////////////////////////////////////////////////
}

void CWorld::Destroy()
{
	for (auto &item : m_ObjectList)
		item->Destroy();
	for (auto &item : m_pObstacleList)
		item->Destroy();
}

void CWorld::Update(float delta)
{
	for (auto &item : m_ObjectList)
		item->Update(delta);
	for (auto &item : m_pObstacleList)
		item->Update(delta);
}

void CWorld::Render()
{
	for (auto &item : m_ObjectList)
		item->Render();
	for (auto &item : m_pObstacleList)
		item->Render();
}

void CWorld::CreateBoid(Vector3D position, float fRadius)
{
	m_ObjectList.push_back(std::make_shared<CBoid>());
	m_ObjectList.back()->Init();
	m_ObjectList.back()->SetPosition(position);
	(dynamic_cast<CBoid*>(m_ObjectList.back().get()))->SetRadius(fRadius);
}

void CWorld::CreateObstacle(Vector3D position, float fRadius)
{
	m_pObstacleList.push_back(std::make_shared<CObstacle>());
	m_pObstacleList.back()->Init();
	m_pObstacleList.back()->SetPosition(position);
	m_pObstacleList.back()->SetRadius(fRadius);

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

CWorld::CWorld()
{
}


CWorld::~CWorld()
{
}

