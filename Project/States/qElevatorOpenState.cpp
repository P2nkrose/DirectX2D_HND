#include "pch.h"
#include "qElevatorOpenState.h"

#include <Scripts/qElevatorScript.h>
#include <Scripts/qPlayerScript.h>

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
}
