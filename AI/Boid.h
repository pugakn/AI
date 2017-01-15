#pragma once
#include "VECTOR4D.h"
class CBoid
{
private:
	VECTOR4D m_velocity;
	VECTOR4D m_position;
	VECTOR4D m_targetPosition;
	float m_fMaxSpeed;
	float m_fMaxAcceleration;

public:
	VECTOR4D Seek();
	VECTOR4D Flee();
	VECTOR4D Arrive();
	void Init();
	void Destroy();
	void Update(float delta);
	void Render();

	void SetTargetPosition(const VECTOR4D& targetPosition);
	void SetMaxSpeed(float fMaxSpeed);
	float GetMaxSpeed();
	void SetMaxAcceleration(float fMaxAcceleration);
	float GetMaxAcceleration();
	CBoid();
	~CBoid();
};

