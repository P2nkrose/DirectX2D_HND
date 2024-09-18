#include "pch.h"
#include "qBossBleedState.h"

#include <Scripts/qBossScript.h>
#include <Scripts/qBleedScript.h>

qBossBleedState::qBossBleedState()
	: qState((UINT)STATE_TYPE::BOSSBLEEDSTATE)
{
}

qBossBleedState::~qBossBleedState()
{
}

void qBossBleedState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(5, 8, false);
}

void qBossBleedState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"BossIdle");
	}
}

void qBossBleedState::Exit()
{
}
