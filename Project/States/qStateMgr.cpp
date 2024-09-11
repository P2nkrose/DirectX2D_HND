#include "pch.h"
#include "qStateMgr.h"

#include "qDeathSoulState.h"
#include "qDoorCloseState.h"
#include "qDoorOpenState.h"
#include "qDoorStayState.h"
#include "qDrownedAttackState.h"
#include "qDrownedDeathState.h"
#include "qDrownedHitState.h"
#include "qDrownedIdleState.h"
#include "qDrownedRunState.h"
#include "qDrownedUturnState.h"
#include "qElevatorCloseState.h"
#include "qElevatorOpenState.h"
#include "qElevatorStayState.h"
#include "qLoadingState.h"
#include "qPlayerBookShootState.h"
#include "qPlayerBumpState.h"
#include "qPlayerCombo1State.h"
#include "qPlayerCombo2State.h"
#include "qPlayerCombo3State.h"
#include "qPlayerCombo4State.h"
#include "qPlayerCrashState.h"
#include "qPlayerDashState.h"
#include "qPlayerEffectState.h"
#include "qPlayerElevatorOutState.h"
#include "qPlayerFallingState.h"
#include "qPlayerIdleState.h"
#include "qPlayerIdleToRunState.h"
#include "qPlayerIdleUTurnState.h"
#include "qPlayerJumpState.h"
#include "qPlayerKrushState.h"
#include "qPlayerLandingState.h"
#include "qPlayerNullState.h"
#include "qPlayerRangeState.h"
#include "qPlayerRunState.h"
#include "qPlayerRunToIdleState.h"
#include "qPlayerRunUTurnState.h"
#include "qPlayerTeleportFinishState.h"
#include "qPlayerTeleportState.h"
#include "qPlayerWaitState.h"
#include "qPostCloseState.h"
#include "qPostOpenState.h"
#include "qSkeletonAttackState.h"
#include "qSkeletonDeathState.h"
#include "qSkeletonIdleState.h"

void qStateMgr::GetStateInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"qDeathSoulState");
	_vec.push_back(L"qDoorCloseState");
	_vec.push_back(L"qDoorOpenState");
	_vec.push_back(L"qDoorStayState");
	_vec.push_back(L"qDrownedAttackState");
	_vec.push_back(L"qDrownedDeathState");
	_vec.push_back(L"qDrownedHitState");
	_vec.push_back(L"qDrownedIdleState");
	_vec.push_back(L"qDrownedRunState");
	_vec.push_back(L"qDrownedUturnState");
	_vec.push_back(L"qElevatorCloseState");
	_vec.push_back(L"qElevatorOpenState");
	_vec.push_back(L"qElevatorStayState");
	_vec.push_back(L"qLoadingState");
	_vec.push_back(L"qPlayerBookShootState");
	_vec.push_back(L"qPlayerBumpState");
	_vec.push_back(L"qPlayerCombo1State");
	_vec.push_back(L"qPlayerCombo2State");
	_vec.push_back(L"qPlayerCombo3State");
	_vec.push_back(L"qPlayerCombo4State");
	_vec.push_back(L"qPlayerCrashState");
	_vec.push_back(L"qPlayerDashState");
	_vec.push_back(L"qPlayerEffectState");
	_vec.push_back(L"qPlayerElevatorOutState");
	_vec.push_back(L"qPlayerFallingState");
	_vec.push_back(L"qPlayerIdleState");
	_vec.push_back(L"qPlayerIdleToRunState");
	_vec.push_back(L"qPlayerIdleUTurnState");
	_vec.push_back(L"qPlayerJumpState");
	_vec.push_back(L"qPlayerKrushState");
	_vec.push_back(L"qPlayerLandingState");
	_vec.push_back(L"qPlayerNullState");
	_vec.push_back(L"qPlayerRangeState");
	_vec.push_back(L"qPlayerRunState");
	_vec.push_back(L"qPlayerRunToIdleState");
	_vec.push_back(L"qPlayerRunUTurnState");
	_vec.push_back(L"qPlayerTeleportFinishState");
	_vec.push_back(L"qPlayerTeleportState");
	_vec.push_back(L"qPlayerWaitState");
	_vec.push_back(L"qPostCloseState");
	_vec.push_back(L"qPostOpenState");
	_vec.push_back(L"qSkeletonAttackState");
	_vec.push_back(L"qSkeletonDeathState");
	_vec.push_back(L"qSkeletonIdleState");
}

qState * qStateMgr::GetState(const wstring& _strStateName)
{
	if (L"qDeathSoulState" == _strStateName)
		return new qDeathSoulState;
	if (L"qDoorCloseState" == _strStateName)
		return new qDoorCloseState;
	if (L"qDoorOpenState" == _strStateName)
		return new qDoorOpenState;
	if (L"qDoorStayState" == _strStateName)
		return new qDoorStayState;
	if (L"qDrownedAttackState" == _strStateName)
		return new qDrownedAttackState;
	if (L"qDrownedDeathState" == _strStateName)
		return new qDrownedDeathState;
	if (L"qDrownedHitState" == _strStateName)
		return new qDrownedHitState;
	if (L"qDrownedIdleState" == _strStateName)
		return new qDrownedIdleState;
	if (L"qDrownedRunState" == _strStateName)
		return new qDrownedRunState;
	if (L"qDrownedUturnState" == _strStateName)
		return new qDrownedUturnState;
	if (L"qElevatorCloseState" == _strStateName)
		return new qElevatorCloseState;
	if (L"qElevatorOpenState" == _strStateName)
		return new qElevatorOpenState;
	if (L"qElevatorStayState" == _strStateName)
		return new qElevatorStayState;
	if (L"qLoadingState" == _strStateName)
		return new qLoadingState;
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
	if (L"qPlayerEffectState" == _strStateName)
		return new qPlayerEffectState;
	if (L"qPlayerElevatorOutState" == _strStateName)
		return new qPlayerElevatorOutState;
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
	if (L"qPlayerNullState" == _strStateName)
		return new qPlayerNullState;
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
	if (L"qSkeletonAttackState" == _strStateName)
		return new qSkeletonAttackState;
	if (L"qSkeletonDeathState" == _strStateName)
		return new qSkeletonDeathState;
	if (L"qSkeletonIdleState" == _strStateName)
		return new qSkeletonIdleState;
	return nullptr;
}

qState * qStateMgr::GetState(UINT _iStateType)
{
	switch (_iStateType)
	{
	case (UINT)STATE_TYPE::DEATHSOULSTATE:
		return new qDeathSoulState;
		break;
	case (UINT)STATE_TYPE::DOORCLOSESTATE:
		return new qDoorCloseState;
		break;
	case (UINT)STATE_TYPE::DOOROPENSTATE:
		return new qDoorOpenState;
		break;
	case (UINT)STATE_TYPE::DOORSTAYSTATE:
		return new qDoorStayState;
		break;
	case (UINT)STATE_TYPE::DROWNEDATTACKSTATE:
		return new qDrownedAttackState;
		break;
	case (UINT)STATE_TYPE::DROWNEDDEATHSTATE:
		return new qDrownedDeathState;
		break;
	case (UINT)STATE_TYPE::DROWNEDHITSTATE:
		return new qDrownedHitState;
		break;
	case (UINT)STATE_TYPE::DROWNEDIDLESTATE:
		return new qDrownedIdleState;
		break;
	case (UINT)STATE_TYPE::DROWNEDRUNSTATE:
		return new qDrownedRunState;
		break;
	case (UINT)STATE_TYPE::DROWNEDUTURNSTATE:
		return new qDrownedUturnState;
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
	case (UINT)STATE_TYPE::LOADINGSTATE:
		return new qLoadingState;
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
	case (UINT)STATE_TYPE::PLAYEREFFECTSTATE:
		return new qPlayerEffectState;
		break;
	case (UINT)STATE_TYPE::PLAYERELEVATOROUTSTATE:
		return new qPlayerElevatorOutState;
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
	case (UINT)STATE_TYPE::PLAYERNULLSTATE:
		return new qPlayerNullState;
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
	case (UINT)STATE_TYPE::SKELETONATTACKSTATE:
		return new qSkeletonAttackState;
		break;
	case (UINT)STATE_TYPE::SKELETONDEATHSTATE:
		return new qSkeletonDeathState;
		break;
	case (UINT)STATE_TYPE::SKELETONIDLESTATE:
		return new qSkeletonIdleState;
		break;
	}
	return nullptr;
}

const wchar_t * qStateMgr::GetStateName(qState * _pState)
{
	switch ((STATE_TYPE)_pState->GetStateType())
	{
	case STATE_TYPE::DEATHSOULSTATE:
		return L"qDeathSoulState";
		break;

	case STATE_TYPE::DOORCLOSESTATE:
		return L"qDoorCloseState";
		break;

	case STATE_TYPE::DOOROPENSTATE:
		return L"qDoorOpenState";
		break;

	case STATE_TYPE::DOORSTAYSTATE:
		return L"qDoorStayState";
		break;

	case STATE_TYPE::DROWNEDATTACKSTATE:
		return L"qDrownedAttackState";
		break;

	case STATE_TYPE::DROWNEDDEATHSTATE:
		return L"qDrownedDeathState";
		break;

	case STATE_TYPE::DROWNEDHITSTATE:
		return L"qDrownedHitState";
		break;

	case STATE_TYPE::DROWNEDIDLESTATE:
		return L"qDrownedIdleState";
		break;

	case STATE_TYPE::DROWNEDRUNSTATE:
		return L"qDrownedRunState";
		break;

	case STATE_TYPE::DROWNEDUTURNSTATE:
		return L"qDrownedUturnState";
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

	case STATE_TYPE::LOADINGSTATE:
		return L"qLoadingState";
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

	case STATE_TYPE::PLAYEREFFECTSTATE:
		return L"qPlayerEffectState";
		break;

	case STATE_TYPE::PLAYERELEVATOROUTSTATE:
		return L"qPlayerElevatorOutState";
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

	case STATE_TYPE::PLAYERNULLSTATE:
		return L"qPlayerNullState";
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

	case STATE_TYPE::SKELETONATTACKSTATE:
		return L"qSkeletonAttackState";
		break;

	case STATE_TYPE::SKELETONDEATHSTATE:
		return L"qSkeletonDeathState";
		break;

	case STATE_TYPE::SKELETONIDLESTATE:
		return L"qSkeletonIdleState";
		break;

	}
	return nullptr;
}