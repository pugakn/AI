#pragma once
#include "State.h"
class CAttack :
	public CState
{
public:

	void Update(std::weak_ptr<CGameObject> callerUnit) override;
	void OnEnter()override;
	void OnExit()override;
	CAttack();
	~CAttack();
};

