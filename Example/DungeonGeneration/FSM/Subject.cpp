#include "Subject.h"
#include <algorithm>


CSubject::CSubject()
{
}


CSubject::~CSubject()
{
}

void CSubject::Notify(float delta)
{
	for (auto &observer : m_observers)
		observer.lock()->Update(delta);
}

void CSubject::Attach(std::weak_ptr<CGameObject> observer)
{
	m_observers.push_back(observer);
}

void CSubject::Detach(std::weak_ptr<CGameObject> observer)
{
	m_observers.erase(std::remove_if(m_observers.begin(), m_observers.end(),
		[observer](const std::weak_ptr<CGameObject>& actual)
	{
		std::shared_ptr<CGameObject> ptr = actual.lock();
		if (actual.lock() == observer.lock())
			return false;
		else
			return true;
	}), m_observers.end());

}
