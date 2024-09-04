#include "pch.h"
#include "qElevatorStayState.h"

#include <Scripts/qElevatorScript.h>
#include <Scripts/qPlayerScript.h>

qElevatorStayState::qElevatorStayState()
{
}

qElevatorStayState::~qElevatorStayState()
{
}

void qElevatorStayState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(6, 15, true);
}

void qElevatorStayState::FinalTick()
{
}

void qElevatorStayState::Exit()
{
}
