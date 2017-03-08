#pragma once
#include "Vector3D.h"
#include <memory>
class CGameObject: public std::enable_shared_from_this<CGameObject>
{
protected:
	Vector3D m_vPosition;
public:
	virtual ~CGameObject() {};
	virtual void Init() = 0;
	virtual void Destroy() = 0;
	virtual void Update(float delta) = 0;
	virtual void Render() = 0;
	Vector3D GetPosition();
	void SetPosition(Vector3D pos);
};

