#pragma once
#include "Vector3D.h" //Está en la carpeta de las Librerias
#include "GameObject.h"
const float MAX_SPEED = 10.f;
const float SEEK_FORCE = 5.f;
const float FLEE_FORCE = 5.f;
const float ARRIVE_FORCE = 5.f;
const float PURSUE_FORCE = 5.f;
const float EVADE_FORCE = 5.f;
const float WANDER_FORCE = 5.f;
const float MAX_TIME_PREDICTION = 1.f;
const float ACTIVE_RADIUS = 5.f;
const float PI = 3.1415927;
class CBoid : public CGameObject
{
private:
	Vector3D m_vVelocity;
	Vector3D m_vTargetPos;
	Vector3D m_vTargetVel;

public:
	Vector3D Seek(const Vector3D& vTargetPosition);
	Vector3D Flee(const Vector3D& vTargetPosition, float fRadius);
	Vector3D Arrive(const Vector3D& vTargetPosition, float fRadius);
	Vector3D Pursue(const Vector3D& vTargetPosition, const Vector3D& vTargetVelocity, float fMaxTimePrediction);
	Vector3D Evade(const Vector3D& vTargetPosition, const Vector3D& vTargetVelocity, float fMaxTimePrediction, float fRadius);
	Vector3D Wander(const Vector3D& vWorldSize, float fRadius, float fMaxTime);
	Vector3D Wander2(const float fOffset, float fRadius, float fVisionRange);
	void Init() override;
	void Destroy() override;
	void Update(float delta) override;
	void Render() override;
	CBoid();
	~CBoid();
	void setTargetPos(Vector3D pos);
	Vector3D getTargetPos();
	void setTargetVel(Vector3D vel);
	Vector3D getTargetVel();
};

