#pragma once
#include "../State.h"
class CAnimStateIdle :
	public CState
{
public:

	void Update(std::weak_ptr<CGameObject> callerUnit) override;
	void OnEnter(std::weak_ptr<CGameObject> callerUnit)override;
	void OnExit(std::weak_ptr<CGameObject> callerUnit)override;
	CAnimStateIdle();
	~CAnimStateIdle();
};