#include "pch.h"
#include "qBossDeathState.h"

#include <Scripts/qBossScript.h>

qBossDeathState::qBossDeathState()
	: qState((UINT)STATE_TYPE::BOSSDEATHSTATE)
{
}

qBossDeathState::~qBossDeathState()
{
}

void qBossDeathState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(7, 10, false);
}

void qBossDeathState::FinalTick()
{
}

void qBossDeathState::Exit()
{
}
