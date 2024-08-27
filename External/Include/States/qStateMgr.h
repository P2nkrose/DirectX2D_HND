#pragma once

#include <vector>
#include <string>

enum STATE_TYPE
{
	PLAYERDASHSTATE,
	PLAYERFALLINGSTATE,
	PLAYERIDLESTATE,
	PLAYERIDLETORUNSTATE,
	PLAYERIDLEUTURNSTATE,
	PLAYERJUMPSTATE,
	PLAYERLANDINGSTATE,
	PLAYERRUNSTATE,
	PLAYERRUNTOIDLESTATE,
	PLAYERRUNUTURNSTATE,
};

using namespace std;

class qState;

class qStateMgr
{
public:
	static void GetStateInfo(vector<wstring>& _vec);
	static qState * GetState(const wstring& _strStateName);
	static qState * GetState(UINT _iStateType);
	static const wchar_t * GetStateName(qState * _pState);
};
