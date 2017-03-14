#pragma once
#include "State.h"
class CIdle :
	public CState
{
public:
	void Update(std::weak_ptr<CGameObject> callerUnit) override;
	void OnEnter()override;
	void OnExit()override;
	CIdle();
	~CIdle();
};

