#include "pch.h"
#include "qDoorOpenState.h"

qDoorOpenState::qDoorOpenState()
{
}

qDoorOpenState::~qDoorOpenState()
{
}

void qDoorOpenState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(2, 10, false);
}

void qDoorOpenState::FinalTick()
{
}

void qDoorOpenState::Exit()
{
}
