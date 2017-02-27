#pragma once
#include "Unit.h"
class CState
{
public:
	CState();
	virtual void Update(float delta, CUnit* callerUnit) = 0;
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	virtual ~CState();
};

