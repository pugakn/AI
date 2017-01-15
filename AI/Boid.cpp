#include "stdafx.h"
#include "Boid.h"


VECTOR4D CBoid::Seek()
{
	VECTOR4D vDirection = Normalize(m_targetPosition - m_position);
	return vDirection * m_fMaxAcceleration;
}

VECTOR4D CBoid::Flee()
{
	VECTOR4D vDirection = Normalize(m_position - m_targetPosition);
	return vDirection * m_fMaxAcceleration;
}

VECTOR4D CBoid::Arrive()
{
	float radius = 5.f;
	VECTOR4D vDistance = m_targetPosition - m_position;
	VECTOR4D vDirection = Normalize(vDistance);
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
	VECTOR4D linearAcceleration = Arrive();
	m_velocity = m_velocity + linearAcceleration * delta;
	if (Magnity(m_velocity) > m_fMaxSpeed) 
	{
		m_velocity =  Normalize(m_velocity);
		m_velocity = m_velocity * m_fMaxSpeed;
	}
	m_position = m_position + m_velocity * delta;

}

void CBoid::Render()
{
}

void CBoid::SetTargetPosition(const VECTOR4D& targetPosition)
{
	m_targetPosition = targetPosition;
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
