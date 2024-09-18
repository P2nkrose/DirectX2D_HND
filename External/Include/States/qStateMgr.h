#pragma once

#include <vector>
#include <string>

enum STATE_TYPE
{
	BOOKEFFECTSTATE,
	BOSSBLEEDSTATE,
	BOSSBLEEDWAVESTATE,
	BOSSDEATHSTATE,
	BOSSHITSTATE,
	BOSSIDLESTATE,
	BOSSINTROSTATE,
	BOSSPUNCHSTATE,
	BOSSRUNSTATE,
	BOSSSLAMFISTSTATE,
	BOSSSLAMSTATE,
	BOSSSTAYSTATE,
	BOSSUTURNSTATE,
	CLAPSTATE,
	DEATHSOULSTATE,
	DOORCLOSESTATE,
	DOOROPENSTATE,
	DOORSTAYSTATE,
	DROWNEDATTACKSTATE,
	DROWNEDDEATHSTATE,
	DROWNEDHITSTATE,
	DROWNEDIDLESTATE,
	DROWNEDRUNSTATE,
	DROWNEDUTURNSTATE,
	ELEVATORCLOSESTATE,
	ELEVATOROPENSTATE,
	ELEVATORSTAYSTATE,
	FIRESTATE,
	GHOSTATTACKSTATE,
	GHOSTDEATHSTATE,
	GHOSTHITSTATE,
	GHOSTIDLESTATE,
	GHOSTRUNSTATE,
	GHOSTUTURNSTATE,
	LOADINGSTATE,
	PLAYERBOOKSHOOTSTATE,
	PLAYERBUMPSTATE,
	PLAYERCOMBO1STATE,
	PLAYERCOMBO2STATE,
	PLAYERCOMBO3STATE,
	PLAYERCOMBO4STATE,
	PLAYERCRASHSTATE,
	PLAYERDASHSTATE,
	PLAYEREFFECTSTATE,
	PLAYERELEVATOROUTSTATE,
	PLAYERFALLINGSTATE,
	PLAYERIDLESTATE,
	PLAYERIDLETORUNSTATE,
	PLAYERIDLEUTURNSTATE,
	PLAYERJUMPSTATE,
	PLAYERKRUSHSTATE,
	PLAYERLANDINGSTATE,
	PLAYERNULLSTATE,
	PLAYERRANGESTATE,
	PLAYERRUNSTATE,
	PLAYERRUNTOIDLESTATE,
	PLAYERRUNUTURNSTATE,
	PLAYERTELEPORTFINISHSTATE,
	PLAYERTELEPORTSTATE,
	PLAYERWAITSTATE,
	POSTCLOSESTATE,
	POSTOPENSTATE,
	SKELETONATTACKSTATE,
	SKELETONDEATHSTATE,
	SKELETONIDLESTATE,
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
