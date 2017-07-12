#pragma once

#include "FSM/State.h"
#include <memory>
#include <list>
#include <vector>
#include "FSM\Subject.h"
class CMarchingSearching : public CState
{
public:
	void Update(std::weak_ptr<CGameObject> callerUnit) override;
	void OnEnter(std::weak_ptr<CGameObject> callerUnit)override;
	void OnExit(std::weak_ptr<CGameObject> callerUnit)override;
};


class CMarchingDone : public CState
{
public:
	void Update(std::weak_ptr<CGameObject> callerUnit) override;
	void OnEnter(std::weak_ptr<CGameObject> callerUnit)override;
	void OnExit(std::weak_ptr<CGameObject> callerUnit)override;

};


class FSMMarchingSq : public CSubject //Hereda de Subject para implementar el patron de diseño observador
{

public:
	enum UNIT_STATES
	{
		DONE,
		SEARCHING
	};
	std::vector<std::shared_ptr<CState>> m_states; //Lista a de todos los estados disponibles

	void Init(CWorld * world);
	void SetState(std::weak_ptr<CGameObject> unit, UNIT_STATES state);
	void Update(float delta);
	void Destroy();
	FSMMarchingSq();
	~FSMMarchingSq();
};



