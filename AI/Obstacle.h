#pragma once
#include "GameObject.h"
class CObstacle : public CGameObject
{
public:
	CObstacle();
	~CObstacle();
	void Init() override;
	void Destroy() override;
	void Update(float delta) override;
	void Render() override;
};

