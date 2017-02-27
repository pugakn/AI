#pragma once
#include "State.h"
class CRoting :
	public CState
{
public:
	void Update(float delta, CUnit* callerUnit) override;
	void OnEnter()override;
	void OnExit()override;
	CRoting();
	~CRoting();
};

