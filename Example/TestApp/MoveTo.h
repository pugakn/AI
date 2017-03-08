#pragma once
#include "State.h"
class CMoveTo :
	public CState
{
public:
	void Update(std::shared_ptr<CGameObject> callerUnit) override;
	void OnEnter()override;
	void OnExit()override;
	void SetFSM(CFSM* fsm) override;
	CMoveTo();
	~CMoveTo();
};

