#include "State.h"


//Se establece el puntero al mundo
void CState::SetWorlPtr(CWorld * ptr)
{
	m_pWorld = ptr;
}
//Se establece el puntero a la máquina de estados
void CState::SetFSM(CFSM * fsm)
{
	m_fsm = fsm;
}
CState::CState()
{
}

CState::~CState()
{
}
