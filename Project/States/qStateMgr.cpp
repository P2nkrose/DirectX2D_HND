#include "pch.h"
#include "qStateMgr.h"

#include "qDoorCloseState.h"
#include "qDoorOpenState.h"
#include "qDoorStayState.h"
#include "qElevatorCloseState.h"
#include "qElevatorOpenState.h"
#include "qElevatorStayState.h"
#include "qPlayerBookShootState.h"
#include "qPlayerBumpState.h"
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
#include "qPlayerTeleportFinishState.h"
#include "qPlayerTeleportState.h"
#include "qPlayerWaitState.h"
#include "qPostCloseState.h"
#include "qPostOpenState.h"

void qStateMgr::GetStateInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"qDoorCloseState");
	_vec.push_back(L"qDoorOpenState");
	_vec.push_back(L"qDoorStayState");
	_vec.push_back(L"qElevatorCloseState");
	_vec.push_back(L"qElevatorOpenState");
	_vec.push_back(L"qElevatorStayState");
	_vec.push_back(L"qPlayerBookShootState");
	_vec.push_back(L"qPlayerBumpState");
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
	_vec.push_back(L"qPlayerTeleportFinishState");
	_vec.push_back(L"qPlayerTeleportState");
	_vec.push_back(L"qPlayerWaitState");
	_vec.push_back(L"qPostCloseState");
	_vec.push_back(L"qPostOpenState");
}

qState * qStateMgr::GetState(const wstring& _strStateName)
{
	if (L"qDoorCloseState" == _strStateName)
		return new qDoorCloseState;
	if (L"qDoorOpenState" == _strStateName)
		return new qDoorOpenState;
	if (L"qDoorStayState" == _strStateName)
		return new qDoorStayState;
	if (L"qElevatorCloseState" == _strStateName)
		return new qElevatorCloseState;
	if (L"qElevatorOpenState" == _strStateName)
		return new qElevatorOpenState;
	if (L"qElevatorStayState" == _strStateName)
		return new qElevatorStayState;
	if (L"qPlayerBookShootState" == _strStateName)
		return new qPlayerBookShootState;
	if (L"qPlayerBumpState" == _strStateName)
		return new qPlayerBumpState;
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
	if (L"qPlayerTeleportFinishState" == _strStateName)
		return new qPlayerTeleportFinishState;
	if (L"qPlayerTeleportState" == _strStateName)
		return new qPlayerTeleportState;
	if (L"qPlayerWaitState" == _strStateName)
		return new qPlayerWaitState;
	if (L"qPostCloseState" == _strStateName)
		return new qPostCloseState;
	if (L"qPostOpenState" == _strStateName)
		return new qPostOpenState;
	return nullptr;
}

qState * qStateMgr::GetState(UINT _iStateType)
{
	switch (_iStateType)
	{
	case (UINT)STATE_TYPE::DOORCLOSESTATE:
		return new qDoorCloseState;
		break;
	case (UINT)STATE_TYPE::DOOROPENSTATE:
		return new qDoorOpenState;
		break;
	case (UINT)STATE_TYPE::DOORSTAYSTATE:
		return new qDoorStayState;
		break;
	case (UINT)STATE_TYPE::ELEVATORCLOSESTATE:
		return new qElevatorCloseState;
		break;
	case (UINT)STATE_TYPE::ELEVATOROPENSTATE:
		return new qElevatorOpenState;
		break;
	case (UINT)STATE_TYPE::ELEVATORSTAYSTATE:
		return new qElevatorStayState;
		break;
	case (UINT)STATE_TYPE::PLAYERBOOKSHOOTSTATE:
		return new qPlayerBookShootState;
		break;
	case (UINT)STATE_TYPE::PLAYERBUMPSTATE:
		return new qPlayerBumpState;
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
	case (UINT)STATE_TYPE::PLAYERTELEPORTFINISHSTATE:
		return new qPlayerTeleportFinishState;
		break;
	case (UINT)STATE_TYPE::PLAYERTELEPORTSTATE:
		return new qPlayerTeleportState;
		break;
	case (UINT)STATE_TYPE::PLAYERWAITSTATE:
		return new qPlayerWaitState;
		break;
	case (UINT)STATE_TYPE::POSTCLOSESTATE:
		return new qPostCloseState;
		break;
	case (UINT)STATE_TYPE::POSTOPENSTATE:
		return new qPostOpenState;
		break;
	}
	return nullptr;
}

const wchar_t * qStateMgr::GetStateName(qState * _pState)
{
	switch ((STATE_TYPE)_pState->GetStateType())
	{
	case STATE_TYPE::DOORCLOSESTATE:
		return L"qDoorCloseState";
		break;

	case STATE_TYPE::DOOROPENSTATE:
		return L"qDoorOpenState";
		break;

	case STATE_TYPE::DOORSTAYSTATE:
		return L"qDoorStayState";
		break;

	case STATE_TYPE::ELEVATORCLOSESTATE:
		return L"qElevatorCloseState";
		break;

	case STATE_TYPE::ELEVATOROPENSTATE:
		return L"qElevatorOpenState";
		break;

	case STATE_TYPE::ELEVATORSTAYSTATE:
		return L"qElevatorStayState";
		break;

	case STATE_TYPE::PLAYERBOOKSHOOTSTATE:
		return L"qPlayerBookShootState";
		break;

	case STATE_TYPE::PLAYERBUMPSTATE:
		return L"qPlayerBumpState";
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

	case STATE_TYPE::PLAYERTELEPORTFINISHSTATE:
		return L"qPlayerTeleportFinishState";
		break;

	case STATE_TYPE::PLAYERTELEPORTSTATE:
		return L"qPlayerTeleportState";
		break;

	case STATE_TYPE::PLAYERWAITSTATE:
		return L"qPlayerWaitState";
		break;

	case STATE_TYPE::POSTCLOSESTATE:
		return L"qPostCloseState";
		break;

	case STATE_TYPE::POSTOPENSTATE:
		return L"qPostOpenState";
		break;

	}
	return nullptr;
}