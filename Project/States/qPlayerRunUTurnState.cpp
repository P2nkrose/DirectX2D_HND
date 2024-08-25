#include "pch.h"
#include "qPlayerRunUTurnState.h"

#include <Scripts/qPlayerScript.h>

qPlayerRunUTurnState::qPlayerRunUTurnState()
{
}

qPlayerRunUTurnState::~qPlayerRunUTurnState()
{
}

void qPlayerRunUTurnState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(6, 15, true);
}

void qPlayerRunUTurnState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		if (KEY_TAP(KEY::LEFT) || KEY_PRESSED(KEY::LEFT) || KEY_TAP(KEY::RIGHT) || KEY_PRESSED(KEY::RIGHT))
		{
			ChangeState(L"Run");
		}
		else
		{
			ChangeState(L"Idle");
		}
	}
}

void qPlayerRunUTurnState::Exit()
{
}
