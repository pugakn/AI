#pragma once
#include "State.h"
class CBuild :
	public CState
{
public:
	void Update(float delta, CUnit* callerUnit) override;
	void OnEnter()override;
	void OnExit()override;
	CBuild();
	~CBuild();
};

