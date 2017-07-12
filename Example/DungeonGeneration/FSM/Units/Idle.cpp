#include "Idle.h"
#include "FSM.h"
#include "../../Unit.h"


void CIdle::Update(std::weak_ptr<CGameObject> callerUnit)
{
	CUnit * unit = nullptr;
	if (callerUnit.lock())
	{
		unit = dynamic_cast<CUnit*>(callerUnit.lock().get());
	}
	else
		return;

	//Si la unidad es belica y ve a un enemigo, cambia al estado de ataque
	if (unit->SeesEnemies() && unit->IsBelic())
	{
		unit->SetNearestTarget();
		m_fsm->SetState(callerUnit,CFSM::UNIT_STATES::ATTACK);
		return;
	}
	return;
}

void CIdle::OnEnter(std::weak_ptr<CGameObject> callerUnit)
{
}

void CIdle::OnExit(std::weak_ptr<CGameObject> callerUnit)
{
}


CIdle::CIdle()
{
}


CIdle::~CIdle()
{
}
