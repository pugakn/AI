#pragma once
#include "State.h"
class CMoveTo :
	public CState
{
public:
	void Update(std::weak_ptr<CGameObject> callerUnit) override;
	void OnEnter()override;
	void OnExit()override;
	CMoveTo();
	~CMoveTo();
};

