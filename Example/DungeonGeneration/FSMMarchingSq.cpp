#include "stdafx.h"
#include "FSMMarchingSq.h"


void FSMMarchingSq::Init(CWorld * world)
{
	m_states.resize(2);
	//Consruir estados y asignar punteros
	m_states[DONE] = std::make_shared<CMarchingDone>();
	//m_states[DONE]->SetFSM(this);
	m_states[DONE]->SetWorlPtr(world);
	m_states[SEARCHING] = std::make_shared<CMarchingSearching>();
	//m_states[SEARCHING]->SetFSM(this);
	m_states[SEARCHING]->SetWorlPtr(world);
}

void FSMMarchingSq::SetState(std::weak_ptr<CGameObject> unit, UNIT_STATES state)
{
}

void FSMMarchingSq::Update(float delta)
{
}

void FSMMarchingSq::Destroy()
{
}

FSMMarchingSq::FSMMarchingSq()
{
}


FSMMarchingSq::~FSMMarchingSq()
{
}

void CMarchingSearching::Update(std::weak_ptr<CGameObject> callerUnit)
{
}

void CMarchingSearching::OnEnter(std::weak_ptr<CGameObject> callerUnit)
{
}

void CMarchingSearching::OnExit(std::weak_ptr<CGameObject> callerUnit)
{
}

void CMarchingDone::Update(std::weak_ptr<CGameObject> callerUnit)
{
}

void CMarchingDone::OnEnter(std::weak_ptr<CGameObject> callerUnit)
{
}

void CMarchingDone::OnExit(std::weak_ptr<CGameObject> callerUnit)
{
}
