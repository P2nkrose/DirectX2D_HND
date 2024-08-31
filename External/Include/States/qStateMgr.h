#pragma once

#include <vector>
#include <string>

enum STATE_TYPE
{
	PLAYERBOOKSHOOTSTATE,
	PLAYERCOMBO1STATE,
	PLAYERCOMBO2STATE,
	PLAYERCOMBO3STATE,
	PLAYERCOMBO4STATE,
	PLAYERCRASHSTATE,
	PLAYERDASHSTATE,
	PLAYERFALLINGSTATE,
	PLAYERIDLESTATE,
	PLAYERIDLETORUNSTATE,
	PLAYERIDLEUTURNSTATE,
	PLAYERJUMPSTATE,
	PLAYERKRUSHSTATE,
	PLAYERLANDINGSTATE,
	PLAYERRANGESTATE,
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
