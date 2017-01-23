#pragma once
#include <list>
#include <memory>
#include "GameObject.h"
class CWorld
{
private:
	std::list <std::shared_ptr<CGameObject>> m_ObjectList;
public:
	void Init();
	void Destroy();
	void Update(float delta);
	void Render();
	CWorld();
	~CWorld();
};

