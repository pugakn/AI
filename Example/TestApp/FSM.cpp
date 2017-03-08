#include "FSM.h"



void CFSM::Update(float delta)
{
	for (auto &observer : m_observers)
		observer->Update(delta);
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

void CFSM::Attach(std::shared_ptr<CGameObject> observer)
{
	m_observers.push_back(observer);
}

void CFSM::Detach(std::shared_ptr<CGameObject> observer)
{
	m_observers.remove(observer);
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

void CFSM::SetState(CUnit* unit, std::shared_ptr<CState> state)
{
	unit->SetState(state);
}
