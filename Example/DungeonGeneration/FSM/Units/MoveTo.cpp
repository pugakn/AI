#include "MoveTo.h"
#include "FSM.h"
#include "Unit.h"


void CMoveTo::Update(std::weak_ptr<CGameObject> callerUnit)
{
	CUnit * unit = nullptr;
	if (callerUnit.lock())
	{
		unit = dynamic_cast<CUnit*>(callerUnit.lock().get());
	}
	else
		return;

	//Si la unidad llegó a su destino, cambia a idle
	if (unit->ArrivedToTargetPos())
	{
		m_fsm->SetState(callerUnit, m_fsm->m_states[States::IDLE]);
		return;
	}
	//La unidad se mueve hacia su destino
	unit->MoveTo(unit->m_targetPos);
}

void CMoveTo::OnEnter()
{
}

void CMoveTo::OnExit()
{
}


CMoveTo::CMoveTo()
{
}


CMoveTo::~CMoveTo()
{
}
