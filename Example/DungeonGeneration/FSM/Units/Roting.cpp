#include "Roting.h"
#include "FSM.h"
#include "../../Unit.h"



void CRoting::Update(std::weak_ptr<CGameObject> callerUnit)
{
	CUnit * unit = nullptr;
	if (callerUnit.lock())
	{
		unit = dynamic_cast<CUnit*>(callerUnit.lock().get());
	}
	else
		return;
	//Si la unidad alacanzó su tiempo máximo de descomposición, cambia a dead
	if (unit->Roted())
	{
		m_fsm->SetState(callerUnit,CFSM::UNIT_STATES::DEAD);
		return;
	}
	//Se incrementa el tiempo de descomposición
	unit->IncRotingTime();
}

void CRoting::OnEnter(std::weak_ptr<CGameObject> callerUnit)
{
	m_fsm->gm.gmLoadAndExecuteScript("GMScripts/stateRoting.gm");
}

void CRoting::OnExit(std::weak_ptr<CGameObject> callerUnit)
{
	//***************************************
	// Reset gmMachine
	//***************************************
	m_fsm->gm.Reset();
}


CRoting::CRoting()
{
}


CRoting::~CRoting()
{
}
