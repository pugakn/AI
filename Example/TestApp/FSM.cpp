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



void CFSM::Init(CWorld * world)
{
	m_states.resize(8);
	//Consruir estados y asignar punteros
	m_states[States::GUARRISON]= std::make_shared<CGuarrison>();
	m_states.back()->SetFSM(this);
	m_states.back()->SetWorlPtr(world);
	m_states[States::BUILD] = std::make_shared<CBuild>();
	m_states.back()->SetFSM(this);
	m_states.back()->SetWorlPtr(world);
	m_states[States::RECOLLECT] = std::make_shared<CRecollect>();
	m_states.back()->SetFSM(this);
	m_states.back()->SetWorlPtr(world);
	m_states[States::ROTING] = std::make_shared<CRoting>();
	m_states.back()->SetFSM(this);
	m_states.back()->SetWorlPtr(world);
	m_states[States::DEAD] = std::make_shared<CDead>();
	m_states.back()->SetFSM(this);
	m_states.back()->SetWorlPtr(world);
	m_states[States::ATTACK] = std::make_shared<CAttack>();
	m_states.back()->SetFSM(this);
	m_states.back()->SetWorlPtr(world);
	m_states[States::MOVE_TO] = std::make_shared<CMoveTo>();
	m_states.back()->SetFSM(this);
	m_states.back()->SetWorlPtr(world);
	m_states[States::IDLE] = std::make_shared<CIdle>();
	m_states.back()->SetFSM(this);
	m_states.back()->SetWorlPtr(world);
}
//Aplicar estado a una unidad
void CFSM::SetState(std::weak_ptr<CGameObject> unit, std::weak_ptr<CState> state)
{
	dynamic_cast<CUnit*>(unit.lock().get())->SetState(state.lock());
}
