#include "Dead.h"
#include "FSM.h"
#include "Unit.h"



void CDead::Update(std::weak_ptr<CGameObject> callerUnit)
{
	CUnit * unit = nullptr;
	if (callerUnit.lock())
	{
		unit = dynamic_cast<CUnit*>(callerUnit.lock().get());
	}
	else
		return;
	//La unidad muere (se elimina de la lista del mundo y se desuscribe de la máquina de estados)
	unit->Die();
}

void CDead::OnEnter()
{
}

void CDead::OnExit()
{
}



CDead::CDead()
{
}


CDead::~CDead()
{
}
