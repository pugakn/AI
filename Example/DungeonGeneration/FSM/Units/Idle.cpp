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
	m_fsm->gm.CallFunction("Update");

	

	////Si la unidad es belica y ve a un enemigo, cambia al estado de ataque
	//if (unit->SeesEnemies() && unit->IsBelic())
	//{
	//	unit->SetNearestTarget();
	//	m_fsm->SetState(callerUnit,CFSM::UNIT_STATES::ATTACK);
	//	return;
	//}
	return;
}

void CIdle::OnEnter(std::weak_ptr<CGameObject> callerUnit)
{
	m_fsm->gm.gmLoadAndExecuteScript("GMScripts/stateIdle.gm");
	m_fsm->gm.CallFunction("OnEnter");
}

void CIdle::OnExit(std::weak_ptr<CGameObject> callerUnit)
{
	m_fsm->gm.CallFunction("OnExit");
	//***************************************
	// Reset gmMachine
	//***************************************
	m_fsm->gm.Reset();
}


CIdle::CIdle()
{
}


CIdle::~CIdle()
{
}
