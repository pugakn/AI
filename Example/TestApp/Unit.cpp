#include "Unit.h"
#include "State.h"



void CUnit::Init()
{
}

void CUnit::Destroy()
{
}

void CUnit::Update(float delta)
{
	m_state.lock()->Update(shared_from_this());
}

void CUnit::Render()
{
}

CUnit::CUnit()
{
}


CUnit::~CUnit()
{
}

bool CUnit::CanRecolect()
{
	return true;
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

void CUnit::TakeDamage(float damage)
{
	m_fHP -= damage;
}

void CUnit::Die()
{
	
}

void CUnit::SetState(std::weak_ptr<CState> state)
{
	m_state.lock()->OnExit();
	m_state = state;
	m_state.lock()->OnEnter();
}


void CUnit::MoveTo(Vector3D poisition)
{
}

void CUnit::Attack(CUnit unit)
{
}

void CUnit::Reload()
{
}

void CUnit::BuildUnit(CUnit unit)
{
}

void CUnit::Guarrison(CUnit unit)
{
}
