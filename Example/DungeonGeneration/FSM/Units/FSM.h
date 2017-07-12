#pragma once
#include "../../Unit.h"
#include "../State.h"
#include <memory>
#include <list>
#include <vector>
#include "../Subject.h"
class CFSM : public CSubject //Hereda de Subject para implementar el patron de diseño observador
{

public:
	enum FSM_TYPE
	{
		ANIM,
		UNIT,
		MARCHING_CUBE
	};
	enum UNIT_STATES
	{
		IDLE,
		MOVE_TO,
		ATTACK,
		DEAD,

		ROTING,
		RECOLLECT,
		BUILD,
		GUARRISON
	};
	std::vector<std::shared_ptr<CState>> m_states; //Lista a de todos los estados disponibles

	void Init(CWorld * world, FSM_TYPE type);
	void SetState(std::weak_ptr<CGameObject> unit, UNIT_STATES state);
	void Update(float delta);
	void Destroy();
	CFSM();
	~CFSM();
private:
	FSM_TYPE m_type;
};

