#pragma once
#include "State.h"
class CMoveTo :
	public CState
{
public:
	void Update(float delta, CUnit* callerUnit) override;
	void OnEnter()override;
	void OnExit()override;
	CMoveTo();
	~CMoveTo();
};

