#include "Dead.h"



void CDead::Update(std::shared_ptr<CGameObject> callerUnit)
{
}

void CDead::OnEnter()
{
}

void CDead::OnExit()
{
}

void CDead::SetFSM(CFSM * fsm)
{
	m_fsm = fsm;
}

CDead::CDead()
{
}


CDead::~CDead()
{
}
