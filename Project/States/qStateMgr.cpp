#include "pch.h"
#include "qStateMgr.h"

#include "qPlayerBookShootState.h"
#include "qPlayerCombo1State.h"
#include "qPlayerCombo2State.h"
#include "qPlayerCombo3State.h"
#include "qPlayerCombo4State.h"
#include "qPlayerCrashState.h"
#include "qPlayerDashState.h"
#include "qPlayerFallingState.h"
#include "qPlayerIdleState.h"
#include "qPlayerIdleToRunState.h"
#include "qPlayerIdleUTurnState.h"
#include "qPlayerJumpState.h"
#include "qPlayerKrushState.h"
#include "qPlayerLandingState.h"
#include "qPlayerRangeState.h"
#include "qPlayerRunState.h"
#include "qPlayerRunToIdleState.h"
#include "qPlayerRunUTurnState.h"

void qStateMgr::GetStateInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"qPlayerBookShootState");
	_vec.push_back(L"qPlayerCombo1State");
	_vec.push_back(L"qPlayerCombo2State");
	_vec.push_back(L"qPlayerCombo3State");
	_vec.push_back(L"qPlayerCombo4State");
	_vec.push_back(L"qPlayerCrashState");
	_vec.push_back(L"qPlayerDashState");
	_vec.push_back(L"qPlayerFallingState");
	_vec.push_back(L"qPlayerIdleState");
	_vec.push_back(L"qPlayerIdleToRunState");
	_vec.push_back(L"qPlayerIdleUTurnState");
	_vec.push_back(L"qPlayerJumpState");
	_vec.push_back(L"qPlayerKrushState");
	_vec.push_back(L"qPlayerLandingState");
	_vec.push_back(L"qPlayerRangeState");
	_vec.push_back(L"qPlayerRunState");
	_vec.push_back(L"qPlayerRunToIdleState");
	_vec.push_back(L"qPlayerRunUTurnState");
}

qState * qStateMgr::GetState(const wstring& _strStateName)
{
	if (L"qPlayerBookShootState" == _strStateName)
		return new qPlayerBookShootState;
	if (L"qPlayerCombo1State" == _strStateName)
		return new qPlayerCombo1State;
	if (L"qPlayerCombo2State" == _strStateName)
		return new qPlayerCombo2State;
	if (L"qPlayerCombo3State" == _strStateName)
		return new qPlayerCombo3State;
	if (L"qPlayerCombo4State" == _strStateName)
		return new qPlayerCombo4State;
	if (L"qPlayerCrashState" == _strStateName)
		return new qPlayerCrashState;
	if (L"qPlayerDashState" == _strStateName)
		return new qPlayerDashState;
	if (L"qPlayerFallingState" == _strStateName)
		return new qPlayerFallingState;
	if (L"qPlayerIdleState" == _strStateName)
		return new qPlayerIdleState;
	if (L"qPlayerIdleToRunState" == _strStateName)
		return new qPlayerIdleToRunState;
	if (L"qPlayerIdleUTurnState" == _strStateName)
		return new qPlayerIdleUTurnState;
	if (L"qPlayerJumpState" == _strStateName)
		return new qPlayerJumpState;
	if (L"qPlayerKrushState" == _strStateName)
		return new qPlayerKrushState;
	if (L"qPlayerLandingState" == _strStateName)
		return new qPlayerLandingState;
	if (L"qPlayerRangeState" == _strStateName)
		return new qPlayerRangeState;
	if (L"qPlayerRunState" == _strStateName)
		return new qPlayerRunState;
	if (L"qPlayerRunToIdleState" == _strStateName)
		return new qPlayerRunToIdleState;
	if (L"qPlayerRunUTurnState" == _strStateName)
		return new qPlayerRunUTurnState;
	return nullptr;
}

qState * qStateMgr::GetState(UINT _iStateType)
{
	switch (_iStateType)
	{
	case (UINT)STATE_TYPE::PLAYERBOOKSHOOTSTATE:
		return new qPlayerBookShootState;
		break;
	case (UINT)STATE_TYPE::PLAYERCOMBO1STATE:
		return new qPlayerCombo1State;
		break;
	case (UINT)STATE_TYPE::PLAYERCOMBO2STATE:
		return new qPlayerCombo2State;
		break;
	case (UINT)STATE_TYPE::PLAYERCOMBO3STATE:
		return new qPlayerCombo3State;
		break;
	case (UINT)STATE_TYPE::PLAYERCOMBO4STATE:
		return new qPlayerCombo4State;
		break;
	case (UINT)STATE_TYPE::PLAYERCRASHSTATE:
		return new qPlayerCrashState;
		break;
	case (UINT)STATE_TYPE::PLAYERDASHSTATE:
		return new qPlayerDashState;
		break;
	case (UINT)STATE_TYPE::PLAYERFALLINGSTATE:
		return new qPlayerFallingState;
		break;
	case (UINT)STATE_TYPE::PLAYERIDLESTATE:
		return new qPlayerIdleState;
		break;
	case (UINT)STATE_TYPE::PLAYERIDLETORUNSTATE:
		return new qPlayerIdleToRunState;
		break;
	case (UINT)STATE_TYPE::PLAYERIDLEUTURNSTATE:
		return new qPlayerIdleUTurnState;
		break;
	case (UINT)STATE_TYPE::PLAYERJUMPSTATE:
		return new qPlayerJumpState;
		break;
	case (UINT)STATE_TYPE::PLAYERKRUSHSTATE:
		return new qPlayerKrushState;
		break;
	case (UINT)STATE_TYPE::PLAYERLANDINGSTATE:
		return new qPlayerLandingState;
		break;
	case (UINT)STATE_TYPE::PLAYERRANGESTATE:
		return new qPlayerRangeState;
		break;
	case (UINT)STATE_TYPE::PLAYERRUNSTATE:
		return new qPlayerRunState;
		break;
	case (UINT)STATE_TYPE::PLAYERRUNTOIDLESTATE:
		return new qPlayerRunToIdleState;
		break;
	case (UINT)STATE_TYPE::PLAYERRUNUTURNSTATE:
		return new qPlayerRunUTurnState;
		break;
	}
	return nullptr;
}

const wchar_t * qStateMgr::GetStateName(qState * _pState)
{
	switch ((STATE_TYPE)_pState->GetStateType())
	{
	case STATE_TYPE::PLAYERBOOKSHOOTSTATE:
		return L"qPlayerBookShootState";
		break;

	case STATE_TYPE::PLAYERCOMBO1STATE:
		return L"qPlayerCombo1State";
		break;

	case STATE_TYPE::PLAYERCOMBO2STATE:
		return L"qPlayerCombo2State";
		break;

	case STATE_TYPE::PLAYERCOMBO3STATE:
		return L"qPlayerCombo3State";
		break;

	case STATE_TYPE::PLAYERCOMBO4STATE:
		return L"qPlayerCombo4State";
		break;

	case STATE_TYPE::PLAYERCRASHSTATE:
		return L"qPlayerCrashState";
		break;

	case STATE_TYPE::PLAYERDASHSTATE:
		return L"qPlayerDashState";
		break;

	case STATE_TYPE::PLAYERFALLINGSTATE:
		return L"qPlayerFallingState";
		break;

	case STATE_TYPE::PLAYERIDLESTATE:
		return L"qPlayerIdleState";
		break;

	case STATE_TYPE::PLAYERIDLETORUNSTATE:
		return L"qPlayerIdleToRunState";
		break;

	case STATE_TYPE::PLAYERIDLEUTURNSTATE:
		return L"qPlayerIdleUTurnState";
		break;

	case STATE_TYPE::PLAYERJUMPSTATE:
		return L"qPlayerJumpState";
		break;

	case STATE_TYPE::PLAYERKRUSHSTATE:
		return L"qPlayerKrushState";
		break;

	case STATE_TYPE::PLAYERLANDINGSTATE:
		return L"qPlayerLandingState";
		break;

	case STATE_TYPE::PLAYERRANGESTATE:
		return L"qPlayerRangeState";
		break;

	case STATE_TYPE::PLAYERRUNSTATE:
		return L"qPlayerRunState";
		break;

	case STATE_TYPE::PLAYERRUNTOIDLESTATE:
		return L"qPlayerRunToIdleState";
		break;

	case STATE_TYPE::PLAYERRUNUTURNSTATE:
		return L"qPlayerRunUTurnState";
		break;

	}
	return nullptr;
}