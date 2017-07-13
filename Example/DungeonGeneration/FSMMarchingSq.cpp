#include "stdafx.h"
#include "FSMMarchingSq.h"
#include "GameObjects\World.h"

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
	bool change = false;



	if (change)
	{
		//Change brother's state
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				int yI = tile->yIndex - 1 + i;
				int xI = tile->xIndex - 1 + i;
				int index = yI * m_pWorld->map.nTilesX + xI;
				m_fsm->SetState(&m_pWorld->map.m_tiles[index], FSMMarchingSq::MARCHING_STATES::SEARCHING);
			}
		}
	}
}

void CMarchingSearching::OnEnter(Tile * tile)
{
}

void CMarchingSearching::OnExit(Tile * tile)
{
}
