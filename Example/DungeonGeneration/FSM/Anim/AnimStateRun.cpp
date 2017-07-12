#include "AnimStateRun.h"
#include "../../Unit.h"
#include "../Units/FSM.h"

void CAnimStateRun::Update(std::weak_ptr<CGameObject> callerUnit)
{
	CUnit * unit = nullptr;
	if (callerUnit.lock())
	{
		unit = dynamic_cast<CUnit*>(callerUnit.lock().get());
	}
	else
		return;

	//Si la unidad llegó a su destino, cambia a idle
	if (unit->ArrivedToTargetPos())
	{
		m_fsm->SetState(callerUnit, CFSM::UNIT_STATES::IDLE);
		return;
	}
	//La unidad se mueve hacia su destino

	unit->m_actualAnim = (Animation::ANIMATION_TYPE)(Animation::ANIMATION_TYPE::runN + unit->m_CoordDir);
}

void CAnimStateRun::OnEnter(std::weak_ptr<CGameObject> callerUnit)
{
	CUnit * unit = nullptr;
	if (callerUnit.lock())
	{
		unit = dynamic_cast<CUnit*>(callerUnit.lock().get());
	}
	else
		return;
	auto dist = Normalize(unit->m_targetPos - unit->GetPosition());
	float angle = atan2f(-(dist.y), (dist.x));
	float t = PI4 / 2.f;
	unit->m_CoordDir = CUnit::DIRECTION::W;
	unit->m_flipSprite = false;
	if (angle > -4 * PI4 + t && angle <  -3 * PI4 + t)
	{
		unit->m_CoordDir = CUnit::DIRECTION::SW;
		unit->m_flipSprite = false;
	}
	else if (angle > -3 * PI4 + t && angle < -2 * PI4 + t)
	{
		unit->m_CoordDir = CUnit::DIRECTION::S;
		unit->m_flipSprite = false;
	}
	else if (angle > -2 * PI4 + t && angle < -1 * PI4 + t)
	{
		unit->m_CoordDir = CUnit::DIRECTION::SW;
		unit->m_flipSprite = true;
	}
	else if (angle > -1 * PI4 + t && angle <   t)
	{
		unit->m_CoordDir = CUnit::DIRECTION::W;
		unit->m_flipSprite = true;
	}
	else if (angle > t && angle < PI4 + t)
	{
		unit->m_CoordDir = CUnit::DIRECTION::NW;
		unit->m_flipSprite = true;
	}
	else if (angle > PI4 + t && angle < 2 * PI4 + t)
	{
		unit->m_CoordDir = CUnit::DIRECTION::N;
		unit->m_flipSprite = false;
	}
	else if (angle > 2 *PI4 + t && angle < 3 * PI4 + t)
	{
		unit->m_CoordDir = CUnit::DIRECTION::NW;
		unit->m_flipSprite = false;
	}
	//else if (angle > 3 * PI4 + t && angle < 4 * PI4 + t)
	//{
		//unit->m_CoordDir = CUnit::DIRECTION::W;
		//unit->m_flipSprite = false;
	//}
}

void CAnimStateRun::OnExit(std::weak_ptr<CGameObject> callerUnit)
{
}

CAnimStateRun::CAnimStateRun()
{
}

CAnimStateRun::~CAnimStateRun()
{
}
