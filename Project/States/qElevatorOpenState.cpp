#include "pch.h"
#include "qElevatorOpenState.h"

#include <Scripts/qElevatorScript.h>
#include <Scripts/qPlayerScript.h>

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qElevatorOpenState::qElevatorOpenState()
{
}

qElevatorOpenState::~qElevatorOpenState()
{
}

void qElevatorOpenState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(7, 15, false);
}

void qElevatorOpenState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"ElevatorStay");
	}
}

void qElevatorOpenState::Exit()
{
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();

	if (pCurLevel->GetName() == L"stage2")
	{
		qGameObject* pPlayer = qLevelMgr::GetInst()->FindObjectByName(L"Player");
		pPlayer->FSM()->ChangeState(L"ElevatorOut");
	}
	if (pCurLevel->GetName() == L"stageboss")
	{
		qGameObject* pPlayer = qLevelMgr::GetInst()->FindObjectByName(L"Player");
		pPlayer->FSM()->ChangeState(L"ElevatorOut");
	}

}
