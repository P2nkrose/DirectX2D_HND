#include "pch.h"
#include "qDoorStayState.h"

#include <Scripts/qPlayerScript.h>
#include <Scripts/qDoorScript.h>

qDoorStayState::qDoorStayState()
{
}

qDoorStayState::~qDoorStayState()
{
}

void qDoorStayState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(1, 10, true);
}

void qDoorStayState::FinalTick()
{
}

void qDoorStayState::Exit()
{
}