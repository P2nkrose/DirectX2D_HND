#include "pch.h"
#include "qBossHitState.h"

#include <Scripts/qBossScript.h>

qBossHitState::qBossHitState()
	: qState((UINT)STATE_TYPE::BOSSHITSTATE)
{
}

qBossHitState::~qBossHitState()
{
}

void qBossHitState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(6, 8, false);
}

void qBossHitState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"BossIdle");
	}
}

void qBossHitState::Exit()
{
}
