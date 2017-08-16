#include "Recollect.h"
#include "FSM.h"
#include "../../Unit.h"


void CRecollect::Update(std::weak_ptr<CGameObject> callerUnit)
{
	CUnit * unit = nullptr;
	if (callerUnit.lock())
	{
		unit = dynamic_cast<CUnit*>(callerUnit.lock().get());
	}
	else
		return;
	//Si la unidad está llena, va a depositar los recursos
	if (unit->IsFull())
	{
		unit->DepositResources();
		return;
	}
	//Si la unidad puede recolectar (esta en el rango), recolecta
	if (unit->CanRecolect(m_pWorld)) {
		unit->Recolect();
		return;
	}
	//Si ninguna de las condiciones anterior se cumple, la unidad se mueve hacia la fuente de recursos más cercana
	unit->MoveToNearestResource();
}

void CRecollect::OnEnter(std::weak_ptr<CGameObject> callerUnit)
{
	m_fsm->gm.gmLoadAndExecuteScript("GMScripts/stateRecollect.gm");
}

void CRecollect::OnExit(std::weak_ptr<CGameObject> callerUnit)
{
	//***************************************
	// Reset gmMachine
	//***************************************
	m_fsm->gm.Reset();
}


CRecollect::CRecollect()
{
}


CRecollect::~CRecollect()
{
}
