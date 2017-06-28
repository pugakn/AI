#include "Obstacle.h"
#include "Matrix4D.h"


CObstacle::CObstacle()
{
}


CObstacle::~CObstacle()
{
}

void CObstacle::Init()
{
	//triangle.Create();
}

void CObstacle::Destroy()
{
	//triangle.Destroy();
}

void CObstacle::Update(float delta)
{
	//Matrix4D transformMTX;
	//transformMTX = Translation(m_vPosition.x, m_vPosition.y,0);
	//triangle.Transform(transformMTX.v);
	
}

void CObstacle::Render()
{
	//triangle.Draw();
}

float CObstacle::GetRadius()
{
	return m_fRadius;
}

void CObstacle::SetRadius(float radius)
{
	m_fRadius = radius;
}
