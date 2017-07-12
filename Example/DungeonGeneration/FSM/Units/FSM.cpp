#include "FSM.h"
#include "Idle.h"
#include "MoveTo.h"
#include "Attack.h"
#include "Dead.h"
#include "Roting.h"
#include "Recollect.h"
#include "Build.h"
#include "Guarrison.h"

#include "../Anim/AnimStateAttack.h"
#include "../Anim/AnimStateIdle.h"
#include "../Anim/AnimStateDie.h"
#include "../Anim/AnimStateRun.h"

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



void CFSM::Init(CWorld * world, FSM_TYPE type)
{
	m_type = type;
	switch (type)
	{
	case CFSM::ANIM:
		m_states.resize(4);
		//Consruir estados y asignar punteros
		m_states[ATTACK] = std::make_shared<CAnimStateAttack>();
		m_states[ATTACK]->SetFSM(this);
		m_states[ATTACK]->SetWorlPtr(world);
		m_states[DEAD] = std::make_shared<CAnimStateDie>();
		m_states[DEAD]->SetFSM(this);
		m_states[DEAD]->SetWorlPtr(world);
		m_states[IDLE] = std::make_shared<CAnimStateIdle>();
		m_states[IDLE]->SetFSM(this);
		m_states[IDLE]->SetWorlPtr(world);
		m_states[MOVE_TO] = std::make_shared<CAnimStateRun>();
		m_states[MOVE_TO] ->SetFSM(this);
		m_states[MOVE_TO] ->SetWorlPtr(world);
		break;
	case CFSM::UNIT:
		m_states.resize(8);
		//Consruir estados y asignar punteros
		m_states[GUARRISON] = std::make_shared<CGuarrison>();
		m_states[GUARRISON] ->SetFSM(this);
		m_states[GUARRISON] ->SetWorlPtr(world);
		m_states[BUILD] = std::make_shared<CBuild>();
		m_states[BUILD] ->SetFSM(this);
		m_states[BUILD] ->SetWorlPtr(world);
		m_states[RECOLLECT] = std::make_shared<CRecollect>();
		m_states[RECOLLECT]->SetFSM(this);
		m_states[RECOLLECT]->SetWorlPtr(world);
		m_states[ROTING] = std::make_shared<CRoting>();
		m_states[ROTING]->SetFSM(this);
		m_states[ROTING]->SetWorlPtr(world);
		m_states[DEAD]= std::make_shared<CDead>();
		m_states[DEAD]->SetFSM(this);
		m_states[DEAD]->SetWorlPtr(world);
		m_states[ATTACK] = std::make_shared<CAttack>();
		m_states[ATTACK] ->SetFSM(this);
		m_states[ATTACK] ->SetWorlPtr(world);
		m_states[MOVE_TO] = std::make_shared<CMoveTo>();
		m_states[MOVE_TO]->SetFSM(this);
		m_states[MOVE_TO]->SetWorlPtr(world);
		m_states[IDLE] = std::make_shared<CIdle>();
		m_states[IDLE]->SetFSM(this);
		m_states[IDLE]->SetWorlPtr(world);
		break;
	case CFSM::MARCHING_CUBE:
		break;
	default:
		break;
	}

}
//Aplicar estado a una unidad
void CFSM::SetState(std::weak_ptr<CGameObject> unit, UNIT_STATES state)
{
	switch (m_type)
	{
	case CFSM::ANIM:
		dynamic_cast<CUnit*>(unit.lock().get())->SetStateAnim(m_states[state]);
		break;
	case CFSM::UNIT:
		dynamic_cast<CUnit*>(unit.lock().get())->SetState(m_states[state]);
		break;
	case CFSM::MARCHING_CUBE:
		break;
	default:
		break;
	}
}
