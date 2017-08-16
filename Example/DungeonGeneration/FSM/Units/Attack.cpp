#include "Attack.h"
#include "../../Unit.h"
#include "FSM.h"



void CAttack::Update(std::weak_ptr<CGameObject> callerUnit)
{
	CUnit* unit = nullptr;
	if (callerUnit.lock())
	{
		unit = dynamic_cast<CUnit*>(callerUnit.lock().get());
	}
	else
		return;


	if (!unit->TargetIsDead())
	{
		//Si la unidad puede atacar, ataca
		if (unit->CanAttack()) {
			unit->AttackTarget();
			return;
		}
		//Si el target no está en rango, la unidad se mueve hacia el
		if (!unit->TargetIsInAttackRange())
		{
			unit->MoveTo(unit->m_target.lock()->m_vPosition);
			return;
		}
		return;
	}
	//Si la unidad ve enemigos, asigna como target el más cercano
	if (unit->SeesEnemies())
	{
		unit->SetNearestTarget();
		return;
	}
	//Si no encuentra a alguien para atacar regresa a idle
	m_fsm->SetState( callerUnit,CFSM::UNIT_STATES::IDLE);
	
}

void CAttack::OnEnter(std::weak_ptr<CGameObject> callerUnit)
{
	m_fsm->gm.gmLoadAndExecuteScript("GMScripts/stateAttack.gm");
}

void CAttack::OnExit(std::weak_ptr<CGameObject> callerUnit)
{
	//***************************************
	// Reset gmMachine
	//***************************************
	m_fsm->gm.Reset();
}



CAttack::CAttack()
{
}


CAttack::~CAttack()
{
}
