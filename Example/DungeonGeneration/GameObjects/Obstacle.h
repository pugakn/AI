#pragma once
#include "GameObject.h"
class CObstacle : public CGameObject
{
private:
	float m_fRadius;
	//TrangleGL triangle;
public:
	CObstacle();
	~CObstacle();
	void Init() override;
	void Destroy() override;
	void Update(float delta) override;
	void Render() override;
	float GetRadius();
	void SetRadius(float radius);
};

