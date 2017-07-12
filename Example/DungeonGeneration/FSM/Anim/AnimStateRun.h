#pragma once
#include "../State.h"
class CAnimStateRun :
	public CState
{
public:

	void Update(std::weak_ptr<CGameObject> callerUnit) override;
	void OnEnter(std::weak_ptr<CGameObject> callerUnit)override;
	void OnExit(std::weak_ptr<CGameObject> callerUnit)override;
	CAnimStateRun();
	~CAnimStateRun();
};