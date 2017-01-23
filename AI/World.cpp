#include "stdafx.h"
#include "World.h"


void CWorld::Init()
{
	for (auto &item : m_ObjectList) 
		item->Init();
}

void CWorld::Destroy()
{
	for (auto &item : m_ObjectList)
		item->Destroy();
}

void CWorld::Update(float delta)
{
	for (auto &item : m_ObjectList)
		item->Update(delta);
}

void CWorld::Render()
{
	for (auto &item : m_ObjectList)
		item->Render();
}

CWorld::CWorld()
{
}


CWorld::~CWorld()
{
}
