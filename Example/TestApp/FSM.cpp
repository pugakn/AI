#include "FSM.h"
#include "Idle.h"
#include "MoveTo.h"
#include "Attack.h"
#include "Dead.h"
#include "Roting.h"
#include "Recollect.h"
#include "Build.h"
#include "Guarrison.h"

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
	//Consruir estados
	m_states.push_back(std::make_shared<CGuarrison>());
	m_states.push_back(std::make_shared<CBuild>());
	m_states.push_back(std::make_shared<CRecollect>());
	m_states.push_back(std::make_shared<CRoting>());
	m_states.push_back(std::make_shared<CDead>());
	m_states.push_back(std::make_shared<CAttack>());
	m_states.push_back(std::make_shared<CMoveTo>());
	m_states.push_back(std::make_shared<CIdle>());
}

void CFSM::SetState(std::weak_ptr<CUnit> unit, std::weak_ptr<CState> state)
{
	unit.lock()->SetState(state.lock());
}
