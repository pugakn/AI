#pragma once
#include "State.h"
class CIdle :
	public CState
{
public:
	void Update(float delta, CUnit* callerUnit) override;
	void OnEnter()override;
	void OnExit()override;
	CIdle();
	~CIdle();
};

