#include "GameObject.h"

Vector3D CGameObject::GetPosition()
{
	return m_vPosition;
}

void CGameObject::SetPosition(Vector3D pos)
{
	m_vPosition = pos;
}
