#include "pch.h"
#include "qPlayerIdleUTurnState.h"

#include <Scripts/qPlayerScript.h>

qPlayerIdleUTurnState::qPlayerIdleUTurnState()
{
}

qPlayerIdleUTurnState::~qPlayerIdleUTurnState()
{
}

void qPlayerIdleUTurnState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(5, 20, true);
}

void qPlayerIdleUTurnState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		if (KEY_TAP(KEY::LEFT) || KEY_PRESSED(KEY::LEFT) || KEY_TAP(KEY::RIGHT) || KEY_PRESSED(KEY::RIGHT))
		{
			ChangeState(L"IdleToRun");
		}
		else
		{
			ChangeState(L"Idle");
		}
	}
}

void qPlayerIdleUTurnState::Exit()
{
}
