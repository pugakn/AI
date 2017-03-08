#include "FSM.h"

void CFSM::Update(float delta)
{
}



void CFSM::Destroy()
{
	
}

CFSM::CFSM()
{
}


CFSM::~CFSM()
{
}



void CFSM::Init()
{
	m_states.push_back(std::make_shared<CIdle>());
	m_states.push_back(std::make_shared<CMoveTo>());
	m_states.push_back(std::make_shared<CAttack>());
	m_states.push_back(std::make_shared<CDead>());
	m_states.push_back(std::make_shared<CRoting>());
	m_states.push_back(std::make_shared<CRecollect>());
	m_states.push_back(std::make_shared<CBuild>());
	m_states.push_back(std::make_shared<CGuarrison>());
}

void CFSM::SetState(std::weak_ptr<CUnit> unit, std::weak_ptr<CState> state)
{
	unit.lock()->SetState(state.lock());
}
