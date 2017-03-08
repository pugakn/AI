#pragma once
//#include "Unit.h"
//#include "FSM.h"
#include <memory>
class CFSM;
class CGameObject;
class CState
{
protected:
	CFSM* m_fsm;
public:
	CState();
	virtual void Update( std::shared_ptr<CGameObject> callerUnit) = 0;
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	virtual void SetFSM(CFSM* fsm) = 0;
	virtual ~CState();
};

