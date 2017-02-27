#pragma once
#include "State.h"
class CRecollect :
	public CState
{
public:
	void Update(float delta, CUnit* callerUnit) override;
	void OnEnter()override;
	void OnExit()override;
	CRecollect();
	~CRecollect();
};

