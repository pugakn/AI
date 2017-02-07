#pragma once
#include "GameObject.h"
#include "Obstacle.h"
#include "TriangleGL.h"
#include <memory>
#include <vector>

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
		kNumObjects
	};
}
const float MAX_SPEED = 0.5f;
const float SEEK_FORCE = 0.5f;
const float FLEE_FORCE = 5.f;
const float ARRIVE_FORCE = 0.2f;
const float PURSUE_FORCE = 0.4f;
const float EVADE_FORCE = 0.4f;
const float WANDER_FORCE = 0.3f;
const float BIG_FORCE = 20000.f;
const float MAX_TIME_PREDICTION = 1.5f;
const float ACTIVE_RADIUS = 0.5f;
const float MAX_FORCE = 0.8f;
const float PROYECTION_DISTANCE = 0.2f;
const float WANDER2_OFFSET = 0.6f;
const float WANDER2_RADIUS = 0.7f;
const float WANDER2_VISIONRANGE = 1.12f;
const float CIRCLE_FORCE = 0.5f;
const float PI = 3.1415927;

const float CIRCLE_RADIUS = 0.5f;
const float CIRCLE_PARAM_VEL = 1.0f;
class CBoid : public CGameObject
{
private:
	TrangleGL triangle;
	Vector3D m_vDirection;
	float m_fRadius;
	float m_fVelocity;
	float m_fCircleParam;

	Vector3D m_vWanderSeekPoint;
	bool m_bWanderArrived = true;
	float m_fWanderTime = 0;

	std::shared_ptr<std::vector<std::shared_ptr<CObstacle>>> m_pObstacleList;
	std::vector <std::pair<std::shared_ptr<CGameObject>, SteeringBehavior::E>> m_Targets;
	std::vector <SteeringStates::E> m_States;

public:
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
	void Init() override;
	void Destroy() override;
	void Update(float delta) override;
	void Render() override;
	CBoid();
	~CBoid();
	
	void SetRadius(float radius);
	float GetRadius();
	float GetVelocity();
	Vector3D GetDirection();
	void SetObstacleList(std::shared_ptr<std::vector<std::shared_ptr<CObstacle>>> pObstacleList);

	void AddStaticTarget( Vector3D targetPos, SteeringBehavior::E key);
	void AddDynamicTarget(std::shared_ptr<CGameObject> target, SteeringBehavior::E key);
	void AddSteeringState(SteeringStates::E state);
};

