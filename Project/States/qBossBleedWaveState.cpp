#include "pch.h"
#include "qBossBleedWaveState.h"

#include <Scripts/qBossScript.h>


qBossBleedWaveState::qBossBleedWaveState()
	: qState((UINT)STATE_TYPE::BOSSBLEEDWAVESTATE)
{
}

qBossBleedWaveState::~qBossBleedWaveState()
{
}

void qBossBleedWaveState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(10, 10, false);
}

void qBossBleedWaveState::FinalTick()
{
}

void qBossBleedWaveState::Exit()
{
}
