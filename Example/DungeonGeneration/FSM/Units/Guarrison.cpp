#include "Guarrison.h"
#include "FSM.h"
#include "../../Unit.h"


void CGuarrison::Update(std::weak_ptr<CGameObject> callerUnit)
{
	CUnit * unit = nullptr;
	if (callerUnit.lock())
	{
		unit = dynamic_cast<CUnit*>(callerUnit.lock().get());
	}
	else
		return;

	//Si la unidad ya está en guarrison, no hace nada
	if (unit->IsInGuarrison())
		return;
	
	if (!unit->TargetIsDead())//Si la unidad en la que vamos a hacer guarrison no está muerta
	{
		if (unit->CanGuarrison()) { //Y la unidad actual puede hacer guarrison en la unidad target
			unit->GuarrisonOnTarget(); //La unidad hace guarrison
			return;
		}
		unit->MoveTo(unit->m_target.lock()->m_vPosition); // Si no está en rango, se mueve hacia el target
		return;
	}
}

void CGuarrison::OnEnter(std::weak_ptr<CGameObject> callerUnit)
{
}

void CGuarrison::OnExit(std::weak_ptr<CGameObject> callerUnit)
{
}



CGuarrison::CGuarrison()
{
}


CGuarrison::~CGuarrison()
{
}
