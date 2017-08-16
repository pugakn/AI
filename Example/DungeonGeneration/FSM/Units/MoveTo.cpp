#include "MoveTo.h"
#include "FSM.h"
#include "../../Unit.h"


void CMoveTo::Update(std::weak_ptr<CGameObject> callerUnit)
{
	CUnit * unit = nullptr;
	if (callerUnit.lock())
	{
		unit = dynamic_cast<CUnit*>(callerUnit.lock().get());
	}
	else
		return;

	m_fsm->gm.CallFunction("Update",unit);
	

	////Si la unidad llegó a su destino, cambia a idle
	//if (unit->ArrivedToTargetPos())
	//{
	//	m_fsm->SetState(callerUnit, CFSM::UNIT_STATES::IDLE);
	//	return;
	//}
	////La unidad se mueve hacia su destino
	//unit->MoveTo(unit->m_targetPos);
}

void CMoveTo::OnEnter(std::weak_ptr<CGameObject> callerUnit)
{
	m_fsm->gm.gmLoadAndExecuteScript("GMScripts/stateMoveTo.gm");
	m_fsm->gm.CallFunction("OnEnter");
}

void CMoveTo::OnExit(std::weak_ptr<CGameObject> callerUnit)
{
	m_fsm->gm.CallFunction("OnExit");
	//***************************************
	// Reset gmMachine
	//***************************************
	m_fsm->gm.Reset();
}


CMoveTo::CMoveTo()
{
}


CMoveTo::~CMoveTo()
{
}
