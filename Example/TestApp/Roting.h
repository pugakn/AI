#pragma once
#include "State.h"
class CRoting :
	public CState
{
public:
	void Update(std::weak_ptr<CGameObject>callerUnit) override;
	void OnEnter()override;
	void OnExit()override;
	void SetFSM(CFSM* fsm) override;
	CRoting();
	~CRoting();
};

