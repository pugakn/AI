#pragma once
#include "State.h"
class CGuarrison :
	public CState
{
public:
	void Update(float delta, CUnit* callerUnit) override;
	void OnEnter()override;
	void OnExit()override;
	CGuarrison();
	~CGuarrison();
};

