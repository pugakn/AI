#include "World.h"
#include "Boid.h"
#include <time.h>
#include <memory>

void CWorld::Init()
{
	srand(time(NULL));
	std::shared_ptr<std::vector<std::shared_ptr<CObstacle>>> obstaclePointer(&m_pObstacleList);
	///////////////////////////////////////////////////////
	//BOIDS//////////////////////////////////////////
	//Inicializar aqui los BOIDS
	///////////////////////////////////////////////////////
	/*CreateBoid(Vector3D(-0.9,-0.5,0), 0.08f);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->SetObstacleList(obstaclePointer);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kObstacleAvoidance);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kWander2);
	CreateBoid(Vector3D(0.9, 0.5, 0), 0.08f);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->SetObstacleList(obstaclePointer);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kObstacleAvoidance);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddDynamicTarget(m_ObjectList[0], SteeringBehavior::E::kPursue);

	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddDynamicTarget(m_ObjectList[1], SteeringBehavior::E::kEvade);

	CreateBoid(Vector3D(0.9, -0.5, 0), 0.08f);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->SetObstacleList(obstaclePointer);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kObstacleAvoidance);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kWander);
	CreateBoid(Vector3D(-0.9, 0.5, 0), 0.08f);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->SetObstacleList(obstaclePointer);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kObstacleAvoidance);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kWander2);

	CreateBoid(Vector3D(-0.9, 0, 0), 0.08f);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->SetObstacleList(obstaclePointer);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kObstacleAvoidance2);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddStaticTarget(Vector3D(0.9,0,0),SteeringBehavior::E::kArrive);

	CreateBoid(Vector3D(-0.9, 0, 0), 0.08f);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->SetObstacleList(obstaclePointer);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kObstacleAvoidance);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kWander);

	CreateBoid(Vector3D(-0.9, 0, 0), 0.08f);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->SetObstacleList(obstaclePointer);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kObstacleAvoidance);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddDynamicTarget(m_ObjectList[5], SteeringBehavior::E::kPursue);*/


	CreateBoid(Vector3D(0.5, 0, 0), 0.08f);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->SetObstacleList(obstaclePointer);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kObstacleAvoidance);
	std::dynamic_pointer_cast<CBoid>(m_ObjectList.back())->AddSteeringState(SteeringStates::E::kCircleMovement);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//OBSTACULOS///////////////////////////////////////////
	//Inicializar aqui los obstaculos 
	///////////////////////////////////////////////////////
	//m_pObstacleList.push_back(std::make_shared<CObstacle>());
	//m_pObstacleList.back()->SetPosition(Vector3D(0, 0.01, 0));
	//m_pObstacleList.back()->SetRadius(0.08f);

	float angulo = rand() / static_cast<float>(RAND_MAX) *6.18; //Angulo random 
	m_pObstacleList.push_back(std::make_shared<CObstacle>());
	m_pObstacleList.back()->SetPosition(Vector3D(sin(angulo) * CIRCLE_RADIUS, cos(angulo)*CIRCLE_RADIUS, 0));
	m_pObstacleList.back()->SetRadius(0.08f);

	angulo = rand() / static_cast<float>(RAND_MAX) *6.18;
	m_pObstacleList.push_back(std::make_shared<CObstacle>());
	m_pObstacleList.back()->SetPosition(Vector3D(sin(angulo) * CIRCLE_RADIUS, cos(angulo)*CIRCLE_RADIUS, 0));	
	m_pObstacleList.back()->SetRadius(0.08f);

	angulo = rand() / static_cast<float>(RAND_MAX) *6.18;
	m_pObstacleList.push_back(std::make_shared<CObstacle>());
	m_pObstacleList.back()->SetPosition(Vector3D(sin(angulo) * CIRCLE_RADIUS, cos(angulo)*CIRCLE_RADIUS, 0));	
	m_pObstacleList.back()->SetRadius(0.08f);

	angulo = rand() / static_cast<float>(RAND_MAX) *6.18;
	m_pObstacleList.push_back(std::make_shared<CObstacle>());
	m_pObstacleList.back()->SetPosition(Vector3D(sin(angulo) * CIRCLE_RADIUS, cos(angulo)*CIRCLE_RADIUS, 0));
	m_pObstacleList.back()->SetRadius(0.08f);
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
