#include "AnimStateDie.h"
#include "../../Unit.h"
#include "../Units/FSM.h"
void CAnimStateDie::Update(std::weak_ptr<CGameObject> callerUnit)
{
	CUnit * unit = nullptr;
	if (callerUnit.lock())
	{
		unit = dynamic_cast<CUnit*>(callerUnit.lock().get());
	}
	else
		return;
	unit->m_actualAnim = (Animation::ANIMATION_TYPE)(Animation::ANIMATION_TYPE::dieN + unit->m_CoordDir);
}

void CAnimStateDie::OnEnter(std::weak_ptr<CGameObject> callerUnit)
{
}

void CAnimStateDie::OnExit(std::weak_ptr<CGameObject> callerUnit)
{
}

CAnimStateDie::CAnimStateDie()
{
}

CAnimStateDie::~CAnimStateDie()
{
}
