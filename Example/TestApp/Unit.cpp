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
	m_state->Update(delta, this);
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
	return m_typeList[m_uIdType]->m_bCanRecolect;
}

bool CUnit::CanBuild()
{
	return m_typeList[m_uIdType]->m_bCanBuild;
}

bool CUnit::IsBelic()
{
	return m_typeList[m_uIdType]->m_bisBelic;
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

void CUnit::SetState(std::shared_ptr<CState> state)
{
	m_state->OnExit();
	m_state = state;
	m_state->OnEnter();
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
