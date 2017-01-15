#include "stdafx.h"
#include "Boid.h"


VECTOR3D CBoid::Seek()
{
	VECTOR3D vDirection = Normalize(m_vTargetPosition - m_vPosition);
	return vDirection * m_fMaxAcceleration;
}

VECTOR3D CBoid::Flee()
{
	VECTOR3D vDirection = Normalize(m_vPosition - m_vTargetPosition);
	return vDirection * m_fMaxAcceleration;
}

VECTOR3D CBoid::Arrive()
{
	float radius = 5.f;
	VECTOR3D vDistance = m_vTargetPosition - m_vPosition;
	VECTOR3D vDirection = Normalize(vDistance);
	if (Magnity(vDistance) > radius)
		return vDirection * m_fMaxAcceleration;
	return (vDirection * m_fMaxAcceleration) * (Magnity(vDistance)/radius);
}

void CBoid::Init()
{
	m_fMaxAcceleration = 5.f;
	m_fMaxSpeed = 50.f;
}

void CBoid::Destroy()
{
}

void CBoid::Update(float delta)
{
	VECTOR3D linearAcceleration = Arrive();
	m_vVelocity = m_vVelocity + linearAcceleration * delta;
	if (Magnity(m_vVelocity) > m_fMaxSpeed) 
	{
		m_vVelocity =  Normalize(m_vVelocity);
		m_vVelocity = m_vVelocity * m_fMaxSpeed;
	}
	m_vPosition = m_vPosition + m_vVelocity * delta;

}

void CBoid::Render()
{
}

void CBoid::SetTargetPosition(const VECTOR3D& targetPosition)
{
	m_vTargetPosition = targetPosition;
}

void CBoid::SetMaxSpeed(float fMaxSpeed)
{
	m_fMaxSpeed = fMaxSpeed;
}

float CBoid::GetMaxSpeed()
{
	return m_fMaxSpeed;
}

void CBoid::SetMaxAcceleration(float fMaxAcceleration)
{
	m_fMaxAcceleration = fMaxAcceleration;
}

float CBoid::GetMaxAcceleration()
{
	return m_fMaxAcceleration;
}

CBoid::CBoid()
{
}


CBoid::~CBoid()
{
}
