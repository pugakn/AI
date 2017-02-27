#pragma once
#include "State.h"
class CDead :
	public CState
{
public:
	void Update(float delta, CUnit* callerUnit) override;
	void OnEnter()override;
	void OnExit()override;
	CDead();
	~CDead();
};

