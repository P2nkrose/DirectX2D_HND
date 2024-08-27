#include "pch.h"
#include "qStateMgr.h"

#include "qPlayerDashState.h"
#include "qPlayerFallingState.h"
#include "qPlayerIdleState.h"
#include "qPlayerIdleToRunState.h"
#include "qPlayerIdleUTurnState.h"
#include "qPlayerJumpState.h"
#include "qPlayerLandingState.h"
#include "qPlayerRunState.h"
#include "qPlayerRunToIdleState.h"
#include "qPlayerRunUTurnState.h"

void qStateMgr::GetStateInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"qPlayerDashState");
	_vec.push_back(L"qPlayerFallingState");
	_vec.push_back(L"qPlayerIdleState");
	_vec.push_back(L"qPlayerIdleToRunState");
	_vec.push_back(L"qPlayerIdleUTurnState");
	_vec.push_back(L"qPlayerJumpState");
	_vec.push_back(L"qPlayerLandingState");
	_vec.push_back(L"qPlayerRunState");
	_vec.push_back(L"qPlayerRunToIdleState");
	_vec.push_back(L"qPlayerRunUTurnState");
}

qState * qStateMgr::GetState(const wstring& _strStateName)
{
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
	if (L"qPlayerLandingState" == _strStateName)
		return new qPlayerLandingState;
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
	case (UINT)STATE_TYPE::PLAYERLANDINGSTATE:
		return new qPlayerLandingState;
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

	case STATE_TYPE::PLAYERLANDINGSTATE:
		return L"qPlayerLandingState";
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