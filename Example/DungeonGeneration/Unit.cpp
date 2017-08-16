#include "Unit.h"
#include "FSM/State.h"
#include "../DungeonGeneration/GameObjects/World.h"

void CUnit::Init()
{
	m_flipSprite = false;
	m_vPosition = Vector3D(0, 0, 0);
	m_actualAnim = Animation::ANIMATION_TYPE::idleN;
	switch (m_uIdType)
	{
	default:
		break;
	}
}

void CUnit::Destroy()
{
}

void CUnit::Update(float delta)
{
	if (m_state.lock())
		m_state.lock()->Update(shared_from_this());
	if (m_animState.lock())
		m_animState.lock()->Update(shared_from_this());
	for (auto &it : animationSet)
	{
		it.Update(delta,m_vPosition, m_flipSprite);
	}
}

void CUnit::Render()
{
	animationSet[m_actualAnim].Render();
}
void CUnit::SetAnimation(char * file)
{
	AnimationLoader animLo;
	animationSet = animLo.Load(("Anim/"+ std::string(file)+ ".anim").c_str());
	for (auto &it : animationSet)
	{
		it.Init();
	}
}

CUnit::CUnit(int id)
{
	m_uId = id;
}


CUnit::~CUnit()
{
}

bool CUnit::CanRecolect(CWorld * world)
{
	return world->GetTypeByID(m_uIdType).m_bCanRecolect;
}

bool CUnit::CanBuild()
{
	return true;
}

bool CUnit::IsBelic()
{
	return true;
}

bool CUnit::IsDead()
{
	return m_fHP <= 0.0f;
}

bool CUnit::TargetIsDead()
{
	return false;
}

bool CUnit::TargetIsEnemy()
{
	return false;
}

bool CUnit::TargetIsInAttackRange()
{
	return false;
}

bool CUnit::IsInGuarrison()
{
	return false;
}

bool CUnit::CanAttack()
{
	return false;
}

bool CUnit::IsFull()
{
	return false;
}

void CUnit::TakeDamage(float damage)
{
	m_fHP -= damage;
}

void CUnit::Die()
{
	
}

void CUnit::SetState(std::weak_ptr<CState> state)
{
	if (m_state.lock())
		m_state.lock()->OnExit(shared_from_this());
	m_state = state;
	m_state.lock()->OnEnter(shared_from_this());
}

void CUnit::SetStateAnim(std::weak_ptr<CState> state)
{
	if (m_animState.lock())
		m_animState.lock()->OnExit(shared_from_this());
	m_animState = state;
	m_animState.lock()->OnEnter(shared_from_this());
}


bool CUnit::SeesEnemies()
{
	return false;
}

bool CUnit::HasBuildOrders()
{
	return false;
}

void CUnit::Build()
{
}

bool CUnit::BuildCompleted()
{
	return false;
}

void CUnit::SearchBuildingUnit()
{
}

bool CUnit::IsInBuildRange()
{
	return false;
}

void CUnit::SetNearestTarget()
{
}

bool CUnit::ArrivedToTargetPos()
{
	auto mag = Magnitude(m_targetPos - m_vPosition);
	if (mag < 1 || mag < 1)
		return true;
	return false;
}

void CUnit::Recolect()
{
}

void CUnit::DepositResources()
{
}

void CUnit::MoveToNearestResource()
{
}

void CUnit::IncRotingTime()
{
}

bool CUnit::Roted()
{
	return false;
}

bool CUnit::CanGuarrison()
{
	return false;
}

void CUnit::MoveTo(Vector3D poisition)
{
	m_vPosition += Normalize(poisition - m_vPosition) ; //DELTA
}

void CUnit::AttackTarget()
{
}

void CUnit::Reload()
{
}

void CUnit::GuarrisonOnTarget()
{
}


