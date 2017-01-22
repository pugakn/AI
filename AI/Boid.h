#pragma once

#include "Vector3D.h" //Y donde esta el archivo?

class CBoid
{
private:
	Vector3D m_vVelocity;
	Vector3D m_vPosition;

	float m_fMaxSpeed;
	float m_fMaxAcceleration;

	const float MAX_SPEED = 10.f; //Si esto ya es una constante, para que quiero la variable m_fMaxSpeed?
	const float SEEK_FORCE = 5.f;
	const float FLEE_FORCE = 5.f;
	const float ARRIVE_FORCE = 5.f;
	const float PURSUE_FORCE = 5.f;
	const float EVADE_FORCE = 5.f;
	const float MAX_TIME_PREDICTION = 1.f;

public:
	Vector3D Seek(const Vector3D& vTargetPosition);
	Vector3D Flee(const Vector3D& vTargetPosition, float fRadius);
	Vector3D Arrive(const Vector3D& vTargetPosition, float fRadius);
	Vector3D Pursue(const Vector3D& vTargetPosition, const Vector3D& vTargetVelocity, float fMaxTimePrediction);
	Vector3D Evade(const Vector3D& vTargetPosition, const Vector3D& vTargetVelocity, float fMaxTimePrediction, float fRadius);
	void Init();
	void Destroy();
	void Update(float delta);
	void Render();
	CBoid();
	~CBoid();
};

