#include "pch.h"
#include "qPlayerElevatorOutState.h"

#include <Scripts/qPlayerScript.h>

qPlayerElevatorOutState::qPlayerElevatorOutState()
{
}

qPlayerElevatorOutState::~qPlayerElevatorOutState()
{
}

void qPlayerElevatorOutState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(11, 15, true);
}

void qPlayerElevatorOutState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"Idle");
	}
}

void qPlayerElevatorOutState::Exit()
{
}
