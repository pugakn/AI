#pragma once
#include "State.h"
class CBuild :
	public CState
{
public:
	void Update(std::weak_ptr<CGameObject> callerUnit) override;
	void OnEnter()override;
	void OnExit()override;
	CBuild();
	~CBuild();
};

