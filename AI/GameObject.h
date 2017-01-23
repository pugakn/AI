#pragma once
#include <Vector3D.h>
class CGameObject
{
protected:
	Vector3D m_vPosition;
public:
	virtual ~CGameObject() {};
	virtual void Init() = 0;
	virtual void Destroy() = 0;
	virtual void Update(float delta) = 0;
	virtual void Render() = 0;
};

