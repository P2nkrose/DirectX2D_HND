#include "pch.h"
#include "qBossSlamFistState.h"

#include <Scripts/qBossScript.h>


qBossSlamFistState::qBossSlamFistState()
	: qState((UINT)STATE_TYPE::BOSSSLAMFISTSTATE)
{
}

qBossSlamFistState::~qBossSlamFistState()
{
}

void qBossSlamFistState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(9, 10, false);
}

void qBossSlamFistState::FinalTick()
{
}

void qBossSlamFistState::Exit()
{
}
