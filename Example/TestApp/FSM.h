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
class CFSM
{
private:
	std::vector<std::shared_ptr<CState>> m_states;
public:
	std::list<std::shared_ptr<CGameObject>> m_observers;
	void Attach(std::shared_ptr<CGameObject> observer);
	void Detach(std::shared_ptr<CGameObject> observer);

	void Init();
	void SetState(CUnit unit, std::shared_ptr<CState> state);
	void Update(float delta);
	void Destroy();
	CFSM();
	~CFSM();
};

