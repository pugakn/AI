#pragma once
#include "State.h"
class CIdle :
	public CState
{
public:
	void Update(std::shared_ptr<CGameObject> callerUnit) override;
	void OnEnter()override;
	void OnExit()override;
	void SetFSM(CFSM* fsm) override;
	CIdle();
	~CIdle();
};

