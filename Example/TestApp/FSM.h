#pragma once
#include "Unit.h"
#include "State.h"
#include "Idle.h"
#include "MoveTo.h"
#include "Attack.h"
#include "Dead.h"
#include "Roting.h"
#include "Recollect.h"
#include "Build.h"
#include "Guarrison.h"
#include <memory>
#include <list>
#include <vector>
#include "Subject.h"
namespace States
{
	enum E
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
}
class CFSM : public CSubject
{
public:
	std::vector<std::shared_ptr<CState>> m_states;


	void Init();
	void SetState(std::weak_ptr<CUnit> unit, std::weak_ptr<CState> state);
	void Update(float delta);
	void Destroy();
	CFSM();
	~CFSM();
};

