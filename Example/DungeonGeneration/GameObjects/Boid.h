#pragma once
#include "GameObject.h"
#include "Obstacle.h"
#include <memory>
#include <vector>
const float PI = 3.1415927;
namespace SteeringBehavior 
{
	enum E
	{
		kSeek,
		kFlee,
		kArrive,
		kPursue,
		kEvade,
		kNumObjects
	};
}
namespace SteeringStates
{
	enum E
	{
		kWander,
		kWander2,
		kObstacleAvoidance,
		kObstacleAvoidance2,
		kCircleMovement,
		kFollowPath,
		kFollowPathLoop,
		kFollowPathArrive,
		kFlocking,
		kFollowTheLider,
		kNumObjects
	};
}
class CBoid : public CGameObject
{
private:
	//========== Constantes Para modificar el comportamiento de las fuerzas ============
	const float MAX_SPEED = 0.6f;
	const float MAX_ROTATION = 0.05f;
	const float BIG_FORCE = 20000.f;
	const float MAX_TIME_PREDICTION = 1.5f;
	const float ACTIVE_RADIUS = 0.05f;
	const float PROYECTION_DISTANCE = 0.05f;

	const float SEEK_FORCE = 0.4f;
	const float FLEE_FORCE = 5.f;
	const float ARRIVE_FORCE = 0.5f;
	const float PURSUE_FORCE = 0.4f;
	const float EVADE_FORCE = 0.4f;
	//Wander
	const float WANDER_FORCE = 0.4f;
	const float WANDER2_OFFSET = 0.4f;
	const float WANDER2_RADIUS = 0.7f;
	const float WANDER2_VISIONRANGE = 1.12f;
	//Circle Movement
	const float CIRCLE_FORCE = 0.5f;
	const float CIRCLE_RADIUS = 0.5f;
	const float CIRCLE_PARAM_VEL = 1.0f;
	//Follow Path
	const float FOLLOW_PATH_LINE_FORCE = 0.1f;
	const float FOLLOW_POINT_RADIUS = 0.02f;
	//Follow the lider
	const float FTL_RADIUS = 1.5f;
	const float FTL_SEEK_MOD = 2.0f;
	const float FTL_SEPARATION_RADIUS = 0.25f;
	const float LIDER_SEPARATION = 0.3f;
	//Flocking
	const float FLOCKING_RADIUS = 0.5f;
	const float FLOCKING_SEPARATION_RADIUS = 0.25f;


	//========= Elementos visuales ==========

	//======== Variables ========
	Vector3D m_vDirection;

	//======== Variables para CircelMovement =========
	float m_fRadius;
	float m_fVelocity;
	float m_fCircleParam;

	//========= Variables para Wander =========
	Vector3D m_vWanderSeekPoint;
	bool m_bWanderArrived = true;
	float m_fWanderTime = 0;

	//========= Variables para FollowPath =========
	int m_iActualPoint;
	bool m_bFirstFollow;
	std::vector<Vector3D> m_followPathVector;

	//========= Variables para FollowTheLider =========
	bool m_isLider;

	//============== Targets y estados ==============
	std::vector <std::pair<std::shared_ptr<CGameObject>, SteeringBehavior::E>> m_Targets;
	std::vector <SteeringStates::E> m_States;

	//======= Boids en el mundo ======
	std::vector<std::shared_ptr<CObstacle>>* m_pObstacleList;
	std::vector<std::shared_ptr<CGameObject>>* m_pWorldBoids;

public:
	//============== Steering Behaviors ==================
	Vector3D Seek(const Vector3D& vTargetPosition);
	Vector3D Flee(const Vector3D& vTargetPosition, float fRadius);
	Vector3D Arrive(const Vector3D& vTargetPosition, float fRadius);
	Vector3D Pursue(const Vector3D& vTargetPosition, const Vector3D& vTargetVelocity, float fMaxTimePrediction);
	Vector3D Evade(const Vector3D& vTargetPosition, const Vector3D& vTargetVelocity, float fMaxTimePrediction, float fRadius);
	Vector3D Wander(const Vector3D& vWorldSize, float fRadius, float fMaxTime, float fDelta);
	Vector3D Wander2(const float fOffset, float fRadius, float fVisionRange);
	Vector3D ObstacleAvoidance(float fProyDist);
	Vector3D ObstacleAvoidance2();
	Vector3D CircleMovement(float fRadius, float delta);
	Vector3D FollowPath();
	Vector3D FollowPathLoop(); //Patrol
	Vector3D FollowPathArrive();
	void SetLider(bool islider);

	Vector3D Separation(float radius);
	Vector3D Cohesion(float radius);
	Vector3D Direction(float radius);
	Vector3D Flocking();
	Vector3D FollowTheLider();



	void Init() override;
	void Destroy() override;
	void Update(float delta) override;
	void Render() override;
	CBoid();
	~CBoid();
	
	bool IsLider();

	//============= Gets, Sets ===============
	void SetRadius(float radius);
	float GetRadius();
	float GetVelocity();
	Vector3D GetDirection();
	void SetWorldBoidsVector(std::vector<std::shared_ptr<CGameObject>>* worldBoids);
	void SetFollowPathVector(std::vector<Vector3D> vector);
	void SetObstacleList(std::vector<std::shared_ptr<CObstacle>>* pObstacleList);

	void AddStaticTarget( Vector3D targetPos, SteeringBehavior::E key);
	void AddDynamicTarget(std::weak_ptr<CGameObject> target, SteeringBehavior::E key);
	void AddSteeringState(SteeringStates::E state);
};

