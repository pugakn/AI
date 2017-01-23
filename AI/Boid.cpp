#include "stdafx.h"
#include "Boid.h"
#include <math.h>


Vector3D CBoid::Seek(const Vector3D& vTargetPosition)
{
	Vector3D vDirection = Normalize(vTargetPosition - m_vPosition);
	return vDirection * SEEK_FORCE;
}

Vector3D CBoid::Flee(const Vector3D& vTargetPosition, float fRadius)
{
	Vector3D vDistance = m_vPosition - vTargetPosition;
	Vector3D vDirection = Normalize(vDistance);
	if (Magnitude(vDistance) > fRadius)
		return Vector3D(0,0,0);
	return vDirection * FLEE_FORCE;
}

Vector3D CBoid::Arrive(const Vector3D& vTargetPosition, float fRadius)
{
	Vector3D vDistance = vTargetPosition - m_vPosition;
	Vector3D vDirection = Normalize(vDistance);
	if (Magnitude(vDistance) > fRadius)
		return vDirection * ARRIVE_FORCE;
	return (vDirection * ARRIVE_FORCE) * (Magnitude(vDistance)/fRadius);
}

Vector3D CBoid::Pursue(const Vector3D & vTargetPosition, const Vector3D & vTargetVelocity, float fMaxTimePrediction)
{
	Vector3D vDistance = vTargetPosition - m_vPosition;
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
	Vector3D vPredictionPos = vTargetPosition + vTargetVelocity * fMaxTimePrediction;
	float fPredictionRadius = Magnitude(vPredictionPos - vTargetPosition);
	if (Magnitude(vDistance) < fPredictionRadius)
	{
		if (Magnitude(vDistance) > fRadius)
			return Vector3D(0,0,0);
		fMaxTimePrediction = Magnitude(vDistance) / fPredictionRadius;
		vPredictionPos = vTargetPosition + vTargetVelocity * fMaxTimePrediction;
	}
	else 
	{
		vDistance = vPredictionPos - m_vPosition;
		if (Magnitude(vDistance) > fRadius)
			return Vector3D(0, 0, 0);
	}
	return Normalize(m_vPosition - vPredictionPos) * EVADE_FORCE;
}

Vector3D CBoid::Wander(const Vector3D & vWorldSize, float fRadius, float fMaxTime)
{
	static Vector3D vSeekPoint;
	static bool bArrived = true;
	Vector3D vDirection;
	if (bArrived) {
		vSeekPoint = Vector3D(rand() % (static_cast<int>(vWorldSize.x) + 1), rand() % (static_cast<int>(vWorldSize.y) + 1), 0);
		vDirection = vSeekPoint - m_vPosition;
		if (Magnitude(vDirection) / Magnitude(m_vVelocity)  > fMaxTime) {
			vSeekPoint = Normalize(vDirection) * fMaxTime * Magnitude(m_vVelocity);
		}
	}
	if (Magnitude(vSeekPoint - m_vPosition) < fRadius) {
		bArrived = true;
		return Vector3D(0, 0, 0);
	}
	return Normalize(vDirection) * WANDER_FORCE;
}

Vector3D CBoid::Wander2(const float fOffset, float fRadius, float fVisionRange)
{
	static Vector3D vForce;
	static Vector3D vPoint;
	static bool bArrived = true;

	if (bArrived) {
		Vector3D vProyectedPoint = m_vPosition + (Normalize(m_vVelocity) * fOffset);
		float fBoidAngle = atan2(m_vVelocity.y, m_vVelocity.x);
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

void CBoid::Init()
{
	m_vVelocity = Vector3D(0, 0, 0);
	m_vPosition = Vector3D(0, 0, 0);
}
void CBoid::Destroy()
{
}

void CBoid::Update(float delta)
{
	Vector3D linearAcceleration =  Arrive(m_vTargetPos,ACTIVE_RADIUS);
	linearAcceleration += Flee(m_vTargetPos, ACTIVE_RADIUS);
	linearAcceleration +=  Seek(m_vTargetPos);
	linearAcceleration += Pursue(m_vTargetPos, m_vTargetVel,MAX_TIME_PREDICTION);
	linearAcceleration += Evade(m_vTargetPos, m_vTargetVel, MAX_TIME_PREDICTION,ACTIVE_RADIUS);
	m_vVelocity += linearAcceleration * delta;
	m_vVelocity = Truncate(m_vVelocity, MAX_SPEED);
	m_vPosition +=  m_vVelocity * delta;

}

void CBoid::Render()
{
}



CBoid::CBoid()
{
}


CBoid::~CBoid()
{
}

void CBoid::setTargetPos(Vector3D pos)
{
	m_vTargetPos = pos;
}

Vector3D CBoid::getTargetPos()
{
	return m_vTargetPos;
}
void CBoid::setTargetVel(Vector3D vel)
{
	m_vTargetPos = vel;
}

Vector3D CBoid::getTargetVel()
{
	return m_vTargetPos;
}
