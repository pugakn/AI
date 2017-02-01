#include "World.h"
#include "Boid.h"
#include <memory>

void CWorld::Init()
{
	std::shared_ptr<std::vector<std::shared_ptr<CObstacle>>> obstaclePointer(&m_pObstacleList);

	CreateBoid(Vector3D(-0.9,-0.5,0), 0.1f);
	dynamic_cast<CBoid*>(m_ObjectList.back().get())->SetObstacleList(obstaclePointer);
	dynamic_cast<CBoid*>(m_ObjectList.back().get())->AddSteeringState(SteeringStates::E::kObstacleAvoidance);
	dynamic_cast<CBoid*>(m_ObjectList.back().get())->AddSteeringState(SteeringStates::E::kWander2);

	//CreateBoid(Vector3D(-0.9, -0.5, 0), 0.1f);
	//dynamic_cast<CBoid*>(m_ObjectList.back().get())->SetObstacleList(obstaclePointer);
	//dynamic_cast<CBoid*>(m_ObjectList.back().get())->AddSteeringState(SteeringStates::E::kObstacleAvoidance);
	//dynamic_cast<CBoid*>(m_ObjectList.back().get())->AddSteeringState(SteeringStates::E::kWander);

	CreateBoid(Vector3D(0.9, 0.5, 0), 0.1f);
	dynamic_cast<CBoid*>(m_ObjectList.back().get())->SetObstacleList(obstaclePointer);
	dynamic_cast<CBoid*>(m_ObjectList.back().get())->AddSteeringState(SteeringStates::E::kObstacleAvoidance);
	dynamic_cast<CBoid*>(m_ObjectList.back().get())->AddDynamicTarget(m_ObjectList[0], SteeringBehabior::E::kPursue);

	dynamic_cast<CBoid*>(m_ObjectList[0].get())->AddDynamicTarget(m_ObjectList[1], SteeringBehabior::E::kEvade);

	CreateBoid(Vector3D(0.9, -0.5, 0), 0.1f);
	dynamic_cast<CBoid*>(m_ObjectList.back().get())->SetObstacleList(obstaclePointer);
	dynamic_cast<CBoid*>(m_ObjectList.back().get())->AddSteeringState(SteeringStates::E::kObstacleAvoidance);
	dynamic_cast<CBoid*>(m_ObjectList.back().get())->AddSteeringState(SteeringStates::E::kWander);
	CreateBoid(Vector3D(-0.9, 0.5, 0), 0.1f);
	dynamic_cast<CBoid*>(m_ObjectList.back().get())->SetObstacleList(obstaclePointer);
	dynamic_cast<CBoid*>(m_ObjectList.back().get())->AddSteeringState(SteeringStates::E::kObstacleAvoidance);
	dynamic_cast<CBoid*>(m_ObjectList.back().get())->AddSteeringState(SteeringStates::E::kWander2);

	//dynamic_cast<CBoid*>(m_ObjectList.back().get())->AddSteeringState(SteeringStates::E::kWander);

	//CreateBoid(Vector3D(-0.9, 0.5, 0), 0.1f);

	//(dynamic_cast<CBoid*>(m_ObjectList.back().get()))->AddDynamicTarget(m_ObjectList[0], SteeringBehabior::E::kPursue);
	//(dynamic_cast<CBoid*>(m_ObjectList.back().get()))->AddSteeringState(SteeringStates::E::kWander2);

	//(dynamic_cast<CBoid*>(m_ObjectList[0].get()))->AddDynamicTarget(m_ObjectList[1], SteeringBehabior::E::kPursue);
	//(dynamic_cast<CBoid*>(m_ObjectList[0].get()))->AddDynamicTarget(m_ObjectList[1], SteeringBehabior::E::kEvade);

	/*OBSTACULOS*///////////////////////////////////////////
	//Inicializar aqui los obstaculos
	m_pObstacleList.push_back(std::make_shared<CObstacle>());
	m_pObstacleList.back()->SetPosition(Vector3D(0, 0.01, 0));
	m_pObstacleList.back()->SetRadius(0.05f);

	m_pObstacleList.push_back(std::make_shared<CObstacle>());
	m_pObstacleList.back()->SetPosition(Vector3D(0, 0.5, 0));
	m_pObstacleList.back()->SetRadius(0.05f);

	m_pObstacleList.push_back(std::make_shared<CObstacle>());
	m_pObstacleList.back()->SetPosition(Vector3D(0, 0.-0.5, 0));
	m_pObstacleList.back()->SetRadius(0.05f);

	m_pObstacleList.push_back(std::make_shared<CObstacle>());
	m_pObstacleList.back()->SetPosition(Vector3D(-0.5, 0.01, 0));
	m_pObstacleList.back()->SetRadius(0.05f);

	m_pObstacleList.push_back(std::make_shared<CObstacle>());
	m_pObstacleList.back()->SetPosition(Vector3D(0.5, 0.01, 0));
	m_pObstacleList.back()->SetRadius(0.05f);
	///////////////////////////////////////////////////////////

	for (auto &item : m_ObjectList) 
		item->Init();
	for (auto &item : m_pObstacleList)
		item->Init();
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

CWorld::CWorld()
{
}


CWorld::~CWorld()
{
}
