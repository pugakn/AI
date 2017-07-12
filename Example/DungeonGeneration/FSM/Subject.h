#pragma once
#include <list>
#include <memory>
#include "../DungeonGeneration/GameObjects/GameObject.h"

class CSubject
{
private:

public:
	std::list<std::weak_ptr<CGameObject>> m_observers;
	CSubject();
	void Notify(float delta);
	void Attach(std::weak_ptr<CGameObject> observer);
	void Detach(std::weak_ptr<CGameObject> observer);
	virtual ~CSubject();
};

