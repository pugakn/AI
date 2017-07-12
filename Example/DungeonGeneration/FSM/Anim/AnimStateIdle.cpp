#include "AnimStateIdle.h"
#include "../../Unit.h"
#include "../Units/FSM.h"

void CAnimStateIdle::Update(std::weak_ptr<CGameObject> callerUnit)
{
	
}

void CAnimStateIdle::OnEnter(std::weak_ptr<CGameObject> callerUnit)
{
	CUnit * unit = nullptr;
	if (callerUnit.lock())
	{
		unit = dynamic_cast<CUnit*>(callerUnit.lock().get());
	}
	unit->m_actualAnim = (Animation::ANIMATION_TYPE)(Animation::ANIMATION_TYPE::idleN + unit->m_CoordDir);
}

void CAnimStateIdle::OnExit(std::weak_ptr<CGameObject> callerUnit)
{
}

CAnimStateIdle::CAnimStateIdle()
{
}

CAnimStateIdle::~CAnimStateIdle()
{
}
