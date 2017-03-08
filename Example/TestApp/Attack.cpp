#include "Attack.h"



void CAttack::Update(std::shared_ptr<CGameObject> callerUnit)
{
}

void CAttack::OnEnter()
{
}

void CAttack::OnExit()
{
}

void CAttack::SetFSM(CFSM * fsm)
{
	m_fsm = fsm;
}

CAttack::CAttack()
{
}


CAttack::~CAttack()
{
}
