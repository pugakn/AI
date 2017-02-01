#include "Boid.h"
#include <math.h>
#include "Matrix4D.h"

Vector3D CBoid::Seek(const Vector3D& vTargetPosition)
{
	Vector3D vDirection = Normalize(vTargetPosition - m_vPosition);
	return vDirection * SEEK_FORCE;
}

Vector3D CBoid::Flee(const Vector3D& vTargetPosition, float fRadius)
{
	Vector3D vDistance = m_vPosition - vTargetPosition;
	if (Magnitude(vDistance) < 0) 
		return Vector3D(0, 0, 0);
	Vector3D vDirection = Normalize(vDistance);
	if (Magnitude(vDistance) > fRadius)
		return Vector3D(0,0,0);
	return vDirection * FLEE_FORCE;
}

Vector3D CBoid::Arrive(const Vector3D& vTargetPosition, float fRadius)
{
	Vector3D vDistance = vTargetPosition - m_vPosition;
	if (Magnitude(vDistance) < 0) 
		return Vector3D(0,0,0);
	Vector3D vDirection = Normalize(vDistance);
	if (Magnitude(vDistance) > fRadius) {
		return vDirection * ARRIVE_FORCE;
	}
	return (vDirection * ARRIVE_FORCE) * (Magnitude(vDistance)/fRadius) ;
}

Vector3D CBoid::Pursue(const Vector3D & vTargetPosition, const Vector3D & vTargetVelocity, float fMaxTimePrediction)
{
	Vector3D vDistance = vTargetPosition - m_vPosition;
	if (Magnitude(vDistance) < 0) 
		return Vector3D(0, 0, 0);
	Vector3D vPredictionPos = vTargetPosition + vTargetVelocity * fMaxTimePrediction;
	float fPredictionRadius = Magnitude(vPredictionPos - vTargetPosition);
	if (Magnitude(vDistance) < fPredictionRadius )
	{
		fMaxTimePrediction = Magnitude(vDistance) / fPredictionRadius;
		vPredictionPos = vTargetPosition + vTargetVelocity * fMaxTimePrediction;
	}
	return Normalize(vPredictionPos - m_vPosition) * PURSUE_FORCE;
}

Vector3D CBoid::Evade(const Vector3D & vTargetPosition, const Vector3D & vTargetVelocity, float fMaxTimePrediction, float fRadius)
{
	Vector3D vDistance = vTargetPosition - m_vPosition;
	if (Magnitude(vDistance) < 0) 
		return Vector3D(0, 0, 0);
	if (Magnitude(vDistance) > fRadius)
		return Vector3D(0,0,0);
	Vector3D vPredictionPos = vTargetPosition + vTargetVelocity * fMaxTimePrediction;
	float fPredictionRadius = Magnitude(vPredictionPos - vTargetPosition);
	if (Magnitude(vDistance) < fPredictionRadius)
	{

		fMaxTimePrediction = Magnitude(vDistance) / fPredictionRadius;
		vPredictionPos = vTargetPosition + vTargetVelocity * fMaxTimePrediction;
	}
	else 
	{
		vDistance = vPredictionPos - m_vPosition;
	}
	return Normalize(m_vPosition - vPredictionPos) * EVADE_FORCE;
}

Vector3D CBoid::Wander(const Vector3D & vWorldSize, float fRadius, float fMaxTime,float fDelta)
{
	static Vector3D vSeekPoint;
	static bool bArrived = true;
	static Vector3D vDirection(1,0,0);
	static float fTime = 0;
	fTime += fDelta;
	if (bArrived) {
		vSeekPoint = Vector3D(-1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - (-1)))), -1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - (-1)))), 0);
		vDirection = vSeekPoint - m_vPosition;
		bArrived = false;
	}
	if (Magnitude(vSeekPoint - m_vPosition) < fRadius) {
		bArrived = true;
		return Vector3D(0, 0, 0);
	}
	if (fTime > fMaxTime) {
		bArrived = true;
	}
	return Normalize(vDirection) * WANDER_FORCE;
}

Vector3D CBoid::Wander2(const float fOffset, float fRadius, float fVisionRange)
{
	static Vector3D vForce;
	static Vector3D vPoint;
	static bool bArrived = true;

	if (bArrived) {
		Vector3D vProyectedPoint = m_vPosition + Vector3D(1,0,0) * fOffset;
		float fBoidAngle = 0;
		if (!(m_vDirection.x == 0 && m_vDirection.y == 0 && m_vDirection.z == 0)) {
			vProyectedPoint = m_vPosition + (Normalize(m_vDirection) * fOffset);
			fBoidAngle = atan2(m_vDirection.y, m_vDirection.x);
		}
		float fRandAngle = (static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (fVisionRange))) - fVisionRange / 2;
		vPoint = vProyectedPoint + Vector3D(cos(fBoidAngle + fRandAngle), sin(fBoidAngle + fRandAngle), 0);
		vForce = Normalize(vPoint - m_vPosition) * WANDER_FORCE;
	}
	if (Magnitude(vPoint - m_vPosition) < fRadius) {
		bArrived = true;
		return Vector3D(0, 0, 0);
	}

	return vForce;
}

Vector3D CBoid::ObstacleAvoidance(float fProyDist)
{
	Vector3D vMedProyection = m_vPosition + fProyDist *0.5f * Normalize(m_vDirection);
	vMedProyection = vMedProyection* Magnitude(m_vDirection);
	Vector3D vFinProyection = vMedProyection * 2.f;
	vFinProyection = vFinProyection* Magnitude(m_vDirection);
	for (auto &item : *m_pObstacleList) {
		if (Magnitude(item->GetPosition() - m_vPosition) < (m_fRadius + item->GetRadius())) {
			//Colisión con boid
			return Normalize(m_vPosition - item->GetPosition()) * BIG_FORCE;
		}
		if (Magnitude(item->GetPosition() - vMedProyection) < (m_fRadius + item->GetRadius())) {
			//Colisión con Medio
			return Normalize(vMedProyection - item->GetPosition()) * BIG_FORCE;
		}
		if (Magnitude(item->GetPosition() - vFinProyection) < (m_fRadius + item->GetRadius())) {
			//Colisión con Final
			return Normalize(vFinProyection - item->GetPosition()) * BIG_FORCE;
		}
	}
	return Vector3D(0, 0, 0);
}
Vector3D CBoid::ObstacleAvoidance2()
{
	return Vector3D(0,0,0);
}



void CBoid::Init()
{
	m_vDirection = Vector3D(0, 0, 0);
	triangle.Create();
}
void CBoid::Destroy()
{
}

void CBoid::Update(float delta)
{
	Vector3D forces(0,0,0);
	for (auto &item : m_Targets) 
	{
		switch (item.second)
		{
		case SteeringBehabior::E::kEvade:
			forces += Evade(item.first->GetPosition(), (dynamic_cast<CBoid*>(item.first.get()))->GetVelocity(),MAX_TIME_PREDICTION,ACTIVE_RADIUS);
			break;
		case SteeringBehabior::E::kFlee:
			forces += Flee(item.first->GetPosition(), ACTIVE_RADIUS);
			break;
		case SteeringBehabior::E::kPursue:
			forces += Pursue(item.first->GetPosition(), (dynamic_cast<CBoid*>(item.first.get()))->GetVelocity(), MAX_TIME_PREDICTION);
			break;
		case SteeringBehabior::E::kSeek:
			forces += Seek(item.first->GetPosition());
			break;
			case SteeringBehabior::E::kArrive :
				forces += Arrive(item.first->GetPosition(), ACTIVE_RADIUS);
			break;
		}
	}

	for (auto &item : m_States)
	{
		switch (item)
		{
		case SteeringStates::E::kWander :
			forces += Wander(Vector3D(1,1,0), 0.05f, 5.f, delta);
			break;
		case SteeringStates::E::kWander2:
			forces += Wander2(WANDER2_OFFSET,WANDER2_RADIUS,WANDER2_VISIONRANGE);
			break;
		case SteeringStates::E::kObstacleAvoidance:
			forces += ObstacleAvoidance(PROYECTION_DISTANCE);
			break;
		}
	}
	Vector3D forces2(0,0,0);
	if (!(forces.x == 0 && forces.y == 0 && forces.z == 0)) {
		forces2 = Normalize(forces);
		m_vDirection += forces2;
		m_vDirection = Normalize(m_vDirection);
	}
	forces = Truncate(forces, MAX_SPEED);
	m_vPosition += m_vDirection * Magnitude(forces) * delta;

	if (m_vPosition.x > 1) {
		m_vPosition.x = -1;
	}
	if (m_vPosition.x < -1) {
		m_vPosition.x = 1;
	}
	if (m_vPosition.y > 1) {
		m_vPosition.y = -1;
	}				
	if (m_vPosition.y < -1) {
		m_vPosition.y = 1;
	}

	Matrix4D traslation;
	traslation = Translation(m_vPosition.x, m_vPosition.y,0);
	triangle.Transform(traslation.v);
}

void CBoid::Render()
{
	triangle.Draw();
}



CBoid::CBoid()
{
}


CBoid::~CBoid()
{
}

Vector3D CBoid::GetVelocity()
{
	return m_vDirection;
}

void CBoid::SetObstacleList(std::shared_ptr<std::vector<std::shared_ptr<CObstacle>>> pObstacleList)
{
	m_pObstacleList = pObstacleList;
}

void CBoid::SetRadius(float radius)
{
	m_fRadius = radius;
}

float CBoid::GetRadius()
{
	return m_fRadius;
}

void CBoid::AddStaticTarget(Vector3D targetPos, SteeringBehabior::E behabior)
{
	std::shared_ptr<CBoid> target = std::make_shared<CBoid>();
	target->Init();
	target->SetPosition(targetPos);
	std::pair<std::shared_ptr<CGameObject>, SteeringBehabior::E> dataPair = { target, behabior };
	m_Targets.push_back(dataPair);
}

void CBoid::AddDynamicTarget(std::shared_ptr <CGameObject> target, SteeringBehabior::E behavior)
{
	std::shared_ptr<CBoid> targetBoid = std::make_shared<CBoid>();
	target->Init();
	std::pair<std::shared_ptr<CGameObject>, SteeringBehabior::E> dataPair = { target, behavior };
	m_Targets.push_back(dataPair);
}

void CBoid::AddSteeringState(SteeringStates::E state)
{
	m_States.push_back(state);
}
