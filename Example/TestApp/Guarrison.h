#pragma once
#include "State.h"
class CGuarrison :
	public CState
{
public:
	void Update(std::weak_ptr<CGameObject> callerUnit) override;
	void OnEnter()override;
	void OnExit()override;
	void SetFSM(CFSM* fsm) override;
	CGuarrison();
	~CGuarrison();
};

