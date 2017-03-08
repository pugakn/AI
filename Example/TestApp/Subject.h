#pragma once
#include <list>
#include <memory>
#include "GameObject.h"

class CSubject
{
private:
	std::list<std::weak_ptr<CGameObject>> m_observers;
public:
	CSubject();
	void Notify(float delta);
	void Attach(std::weak_ptr<CGameObject> observer);
	void Detach(std::weak_ptr<CGameObject> observer);
	virtual ~CSubject();
};

