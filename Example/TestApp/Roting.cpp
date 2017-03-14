#include "Roting.h"
#include "FSM.h"
#include "Unit.h"



void CRoting::Update(std::weak_ptr<CGameObject> callerUnit)
{
	CUnit * unit = nullptr;
	if (callerUnit.lock())
	{
		unit = dynamic_cast<CUnit*>(callerUnit.lock().get());
	}
	else
		return;
	//Si la unidad alacanz� su tiempo m�ximo de descomposici�n, cambia a dead
	if (unit->Roted())
	{
		m_fsm->SetState(callerUnit, m_fsm->m_states[States::DEAD]);
		return;
	}
	//Se incrementa el tiempo de descomposici�n
	unit->IncRotingTime();
}

void CRoting::OnEnter()
{
}

void CRoting::OnExit()
{
}


CRoting::CRoting()
{
}


CRoting::~CRoting()
{
}
