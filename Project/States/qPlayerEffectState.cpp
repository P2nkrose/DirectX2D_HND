#include "pch.h"
#include "qPlayerEffectState.h"

qPlayerEffectState::qPlayerEffectState()
	: qState((UINT)STATE_TYPE::PLAYEREFFECTSTATE)
{
}

qPlayerEffectState::~qPlayerEffectState()
{
}

void qPlayerEffectState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(0, 30, true);
}

void qPlayerEffectState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		GetOwner()->Destroy();
	}
}

void qPlayerEffectState::Exit()
{
}
