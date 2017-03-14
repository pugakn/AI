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
				//Si la unidad terminó lo que estaba construyendo, busca otra cosa para construír.
				unit->SearchBuildingUnit();
				return;
			}
			//Si la unidad está en el rago de construcción, construye lo que tenga primero en su cola de construcción
			unit->Build();
			return;
		}
		//Si la unidad no está en el rango de construcción, se mueve
		unit->MoveTo(unit->m_target.lock()->m_vPosition);
	}
	//Si no se cumple ninguna condición anterios, la unidad sólo se mantiene esperando a que le den algo para construír.
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
