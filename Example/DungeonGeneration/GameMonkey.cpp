#include "stdafx.h"
#include "GameMonkey.h"
#include <gmCall.h>

using namespace std;


CGameMonkey::CGameMonkey()
{
	//m_gmMachine = new gmMachine();
	RegisterFunctions();
}


CGameMonkey::~CGameMonkey()
{
	//delete m_gmMachine;
	//m_gmMachine.ResetAndFreeMemory();
}

int CGameMonkey::gmLoadAndExecuteScript( const char *a_filename)
{
	std::ifstream file(a_filename);
	if (!file)
		return GM_EXCEPTION;

	std::string fileString = std::string(std::istreambuf_iterator<char>(file),
		std::istreambuf_iterator<char>());
	file.close();
	return m_gmMachine.ExecuteString(fileString.c_str());
}

void CGameMonkey::handleErrors()
{
	gmLog &log = m_gmMachine.GetLog();
	// Get the first error
	bool firstError = true;
	const char *err = log.GetEntry(firstError);
	while (err)
	{
		std::cout << "Compilation error: -" << err << std::endl;
		err = log.GetEntry(firstError);
	}
}
#include "Unit.h"

bool CGameMonkey::CallFunction(const char * name,CUnit* param1)
{
	gmCall call;
	if (call.BeginGlobalFunction(& m_gmMachine, name))
	{
		// Push the parameters
		//call.AddParamInt(param1);
		call.AddParamUser(m_gmMachine.AllocUserObject(param1, CGameMonkey::GM_TYPE::T_UNIT));
		// Execute the call
		call.End();
		return true;
	}
	else
	{
		std::cout << "Error calling " << name << std::endl;
		return false;
	}
}

bool CGameMonkey::CallFunction(const char * name)
{
	gmCall call;
	if (call.BeginGlobalFunction(&m_gmMachine, name))
	{
		// Execute the call
		call.End();
		return true;
	}
	else
	{
		std::cout << "Error calling " << name << std::endl;
		return false;
	}
}

void CGameMonkey::Reset()
{
	//m_gmMachine.ResetAndFreeMemory();
	//m_gmMachine = new gmMachine();
	RegisterFunctions();
}
#include "GMFunctions.h"
void CGameMonkey::RegisterFunctions()
{
	m_gmMachine.RegisterLibraryFunction("MoveTo", gmUnit::gms_MoveTo);
	m_gmMachine.RegisterLibraryFunction("SetState", gmUnit::gms_SetState);
	m_gmMachine.RegisterLibraryFunction("ArrivedToTargetPos", gmUnit::gms_ArrivedToTargetPos);
}





