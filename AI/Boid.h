#pragma once
#include "VECTOR3D.h"
class CBoid
{
private:
	VECTOR3D m_vVelocity;
	VECTOR3D m_vPosition;
	VECTOR3D m_vTargetPosition;
	float m_fMaxSpeed;
	float m_fMaxAcceleration;

public:
	VECTOR3D Seek();
	VECTOR3D Flee();
	VECTOR3D Arrive();
	void Init();
	void Destroy();
	void Update(float delta);
	void Render();

	void SetTargetPosition(const VECTOR3D& targetPosition);
	void SetMaxSpeed(float fMaxSpeed);
	float GetMaxSpeed();
	void SetMaxAcceleration(float fMaxAcceleration);
	float GetMaxAcceleration();
	CBoid();
	~CBoid();
};

