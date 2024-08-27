#include "pch.h"
#include "qPlayerCombo1EndState.h"

#include <Scripts/qPlayerScript.h>

qPlayerCombo1EndState::qPlayerCombo1EndState()
{
}

qPlayerCombo1EndState::~qPlayerCombo1EndState()
{
}

void qPlayerCombo1EndState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(14, 10, false);
}

void qPlayerCombo1EndState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"Idle");
	}
}

void qPlayerCombo1EndState::Exit()
{
}
