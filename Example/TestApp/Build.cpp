#include "Build.h"
#include "FSM.h"
#include "Unit.h"


void CBuild::Update(std::weak_ptr<CGameObject> callerUnit)
{
	CUnit * unit = nullptr;
	if (callerUnit.lock())
	{
		unit = dynamic_cast<CUnit*>(callerUnit.lock().get());
	}
	else
		return;
	if (unit->HasBuildOrders())
	{
		if (unit->IsInBuildRange())
		{
			if (unit->BuildCompleted())
			{
				//Si la unidad termin� lo que estaba construyendo, busca otra cosa para constru�r.
				unit->SearchBuildingUnit();
				return;
			}
			//Si la unidad est� en el rago de construcci�n, construye lo que tenga primero en su cola de construcci�n
			unit->Build();
			return;
		}
		//Si la unidad no est� en el rango de construcci�n, se mueve
		unit->MoveTo(unit->m_target.lock()->m_vPosition);
	}
	//Si no se cumple ninguna condici�n anterios, la unidad s�lo se mantiene esperando a que le den algo para constru�r.
	unit->SearchBuildingUnit();
}

void CBuild::OnEnter()
{
}

void CBuild::OnExit()
{
}


CBuild::CBuild()
{
}


CBuild::~CBuild()
{
}
