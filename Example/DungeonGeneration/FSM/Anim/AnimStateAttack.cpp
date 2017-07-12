#include "AnimStateAttack.h"
#include "../../Unit.h"
#include "../Units/FSM.h"
void CAnimStateAttack::Update(std::weak_ptr<CGameObject> callerUnit)
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
			unit->m_actualAnim = (Animation::ANIMATION_TYPE)(Animation::ANIMATION_TYPE::attackN + unit->m_CoordDir);
			unit->AttackTarget();
			return;
		}
		//Si el target no está en rango, la unidad se mueve hacia el
		if (!unit->TargetIsInAttackRange())
		{
			unit->m_actualAnim = (Animation::ANIMATION_TYPE)(Animation::ANIMATION_TYPE::runN + unit->m_CoordDir);
			return;
		}
		return;
	}
	unit->m_actualAnim = (Animation::ANIMATION_TYPE)(Animation::ANIMATION_TYPE::idleN + unit->m_CoordDir);
}

void CAnimStateAttack::OnEnter(std::weak_ptr<CGameObject> callerUnit)
{
}

void CAnimStateAttack::OnExit(std::weak_ptr<CGameObject> callerUnit)
{
}

CAnimStateAttack::CAnimStateAttack()
{
}

CAnimStateAttack::~CAnimStateAttack()
{
}
