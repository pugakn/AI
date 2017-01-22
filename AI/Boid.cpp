#include "stdafx.h"
#include "Boid.h"


Vector3D CBoid::Seek(const Vector3D& vTargetPosition)
{
	Vector3D vDirection = Normalize(vTargetPosition - m_vPosition);
	return vDirection * SEEK_FORCE;
}

Vector3D CBoid::Flee(const Vector3D& vTargetPosition, float fRadius)
{
	Vector3D vDistance = m_vPosition - vTargetPosition;
	Vector3D vDirection = Normalize(vDistance);
	if (Magnity(vDistance) > fRadius) //La palabra es Magnitude
		return Vector3D(0,0,0);
	return vDirection * FLEE_FORCE;
}

Vector3D CBoid::Arrive(const Vector3D& vTargetPosition, float fRadius)
{
	Vector3D vDistance = vTargetPosition - m_vPosition;
	Vector3D vDirection = Normalize(vDistance);
	if (Magnity(vDistance) > fRadius)
		return vDirection * ARRIVE_FORCE;
	return (vDirection * ARRIVE_FORCE) * (Magnity(vDistance)/fRadius);
}

Vector3D CBoid::Pursue(const Vector3D & vTargetPosition, const Vector3D & vTargetVelocity, float fMaxTimePrediction)
{
	Vector3D vDistance = vTargetPosition - m_vPosition;
	Vector3D vPredictionPos = vTargetPosition + vTargetVelocity * fMaxTimePrediction;
	float fPredictionRadius = Magnity(vPredictionPos - vTargetPosition);
	if (Magnity(vDistance) < fPredictionRadius )
	{
		fMaxTimePrediction = Magnity(vDistance) / fPredictionRadius;
		vPredictionPos = vTargetPosition + vTargetVelocity * fMaxTimePrediction;
	}
	return Normalize(vPredictionPos - m_vPosition) * PURSUE_FORCE;
}

Vector3D CBoid::Evade(const Vector3D & vTargetPosition, const Vector3D & vTargetVelocity, float fMaxTimePrediction, float fRadius)
{
	Vector3D vDistance = vTargetPosition - m_vPosition;
	Vector3D vPredictionPos = vTargetPosition + vTargetVelocity * fMaxTimePrediction;
	float fPredictionRadius = Magnity(vPredictionPos - vTargetPosition);
	if (Magnity(vDistance) < fPredictionRadius)
	{
		if (Magnity(vDistance) > fRadius)
			return Vector3D(0,0,0);
		fMaxTimePrediction = Magnity(vDistance) / fPredictionRadius;
		vPredictionPos = vTargetPosition + vTargetVelocity * fMaxTimePrediction;
	}
	else 
	{
		vDistance = vPredictionPos - m_vPosition;
		if (Magnity(vDistance) > fRadius)
			return Vector3D(0, 0, 0);
	}
	return Normalize(vPredictionPos - m_vPosition) * EVADE_FORCE;
}

void CBoid::Init()
{
}

void CBoid::Destroy()
{
}

void CBoid::Update(float delta)
{
  //Por que tenemos constantes hardcodeadas aqui...
  //Agregue variables segun se requiera, no hardcodee nada
	Vector3D linearAcceleration =  Arrive(Vector3D(1,1,1), 5.0f);
	linearAcceleration += Flee(Vector3D(10, 1, 1), 5.0f);
	linearAcceleration +=  Seek(Vector3D(5, 1, 1));
	linearAcceleration += Pursue(Vector3D(5, 1, 1),Vector3D(1,1,0),MAX_TIME_PREDICTION);
	linearAcceleration += Evade(Vector3D(5, 1, 1), Vector3D(5, 0, 0), MAX_TIME_PREDICTION,5.0f);
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
