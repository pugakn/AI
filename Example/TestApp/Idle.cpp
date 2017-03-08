#include "Idle.h"
#include "FSM.h"
#include "Unit.h"


void CIdle::Update(std::weak_ptr<CGameObject> callerUnit)
{
	//if (callerUnit->SeesEnemies())
	//{
	//	//m_fsm->SetState(callerUnit,m_fsm->m_states[States::ATTACK]);
	//	return;
	//}
	//return;
}

void CIdle::OnEnter()
{
}

void CIdle::OnExit()
{
}

void CIdle::SetFSM(CFSM * fsm)
{
	m_fsm = fsm;
}

CIdle::CIdle()
{
}


CIdle::~CIdle()
{
}
