#include "pch.h"
#include "qPlayerCrashState.h"

#include <Scripts/qPlayerScript.h>

qPlayerCrashState::qPlayerCrashState()
{
}

qPlayerCrashState::~qPlayerCrashState()
{
}

void qPlayerCrashState::Enter()
{
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativeScale(550.f, 550.f, 0.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.237f, 0.237f, 0.f));

	GetOwner()->FlipBookComponent()->Play(18, 15, false);
}

void qPlayerCrashState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"Idle");
	}
}

void qPlayerCrashState::Exit()
{
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
