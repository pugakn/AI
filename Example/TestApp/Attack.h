#pragma once
#include "State.h"
class CAttack :
	public CState
{
public:

	void Update(float delta , CUnit* callerUnit) override;
	void OnEnter()override;
	void OnExit()override;
	CAttack();
	~CAttack();
};

