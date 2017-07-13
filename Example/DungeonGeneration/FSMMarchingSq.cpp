#include "stdafx.h"
#include "FSMMarchingSq.h"


void FSMMarchingSq::Init(CWorld * world)
{
	m_states.resize(2);
	//Consruir estados y asignar punteros
	m_states[DONE] = std::make_shared<CMarchingDone>();
	m_states[DONE]->SetFSM(this);
	m_states[DONE]->SetWorlPtr(world);
	m_states[SEARCHING] = std::make_shared<CMarchingSearching>();
	m_states[SEARCHING]->SetFSM(this);
	m_states[SEARCHING]->SetWorlPtr(world);
}

void FSMMarchingSq::SetState(Tile * tile, MARCHING_STATES state)
{
	tile->m_state = m_states[state];
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

void CMarchingState::SetWorlPtr(CWorld * ptr)
{
	m_pWorld = ptr;
}

CMarchingState::CMarchingState()
{
}


void CMarchingState::SetFSM(FSMMarchingSq * fsm)
{
	m_fsm = fsm;
}

CMarchingState::~CMarchingState()
{
}

void CMarchingDone::Update(Tile * tile)
{

}

void CMarchingDone::OnEnter(Tile * tile)
{
}

void CMarchingDone::OnExit(Tile * tile)
{
}

void CMarchingSearching::Update(Tile * tile)
{
	//Search for corners

}

void CMarchingSearching::OnEnter(Tile * tile)
{
}

void CMarchingSearching::OnExit(Tile * tile)
{
}
