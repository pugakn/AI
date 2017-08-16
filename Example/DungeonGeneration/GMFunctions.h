#pragma once
#include "Unit.h"
#include <gmThread.h>
#include <iostream>
#include "GameMonkey.h"
#include "FSM\Units\FSM.h"
struct gmUnit {
	static CFSM* pFSM;
	static int _cdecl gms_MoveTo(gmThread * a_thread) {
		GM_CHECK_NUM_PARAMS(1);
		//GM_CHECK_INT_PARAM(unitID, 1);
		GM_CHECK_USER_PARAM(CUnit*, CGameMonkey::GM_TYPE::T_UNIT, userObj,0);
		CUnit* unit = (CUnit*)userObj;
		unit->MoveTo(unit->m_targetPos);    
		//std::cout << "MoveTo() " ;
		return GM_OK;
	}
	static int _cdecl gms_SetState(gmThread * a_thread) {
		GM_CHECK_NUM_PARAMS(2);
		GM_CHECK_USER_PARAM(CUnit*, CGameMonkey::GM_TYPE::T_UNIT, userObj, 0);
		GM_CHECK_INT_PARAM(state, 1);
		CUnit* unit = (CUnit*)userObj;
		unit->SetState(pFSM->m_states[state]);
		return GM_OK;
	}
	static int _cdecl gms_ArrivedToTargetPos(gmThread * a_thread) {
		GM_CHECK_NUM_PARAMS(1);
		GM_CHECK_USER_PARAM(CUnit*, CGameMonkey::GM_TYPE::T_UNIT, userObj, 0);
		CUnit* unit = (CUnit*)userObj;
		a_thread->PushInt(unit->ArrivedToTargetPos());
		return GM_OK;
	}
};
