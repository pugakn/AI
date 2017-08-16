#pragma once
#include <gmThread.h>
#include <fstream>
#include <iostream>
#include <iterator>
class CUnit;
class CGameMonkey
{
public:
	enum GM_TYPE
	{
		T_UNIT= 7
	};
	gmMachine m_gmMachine;
	int gmLoadAndExecuteScript( const char *a_filename);
	void handleErrors();
	bool CallFunction(const char* name, CUnit* param1);
	bool CallFunction(const char* name);
	void Reset();
	void RegisterFunctions();
	CGameMonkey();
	~CGameMonkey();
};

