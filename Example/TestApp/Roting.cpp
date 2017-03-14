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
	//Si la unidad alacanzó su tiempo máximo de descomposición, cambia a dead
	if (unit->Roted())
	{
		m_fsm->SetState(callerUnit, m_fsm->m_states[States::DEAD]);
		return;
	}
	//Se incrementa el tiempo de descomposición
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
