#include "pch.h"
#include "qPlayerRangeState.h"

#include <Scripts/qPlayerScript.h>

qPlayerRangeState::qPlayerRangeState()
{
}

qPlayerRangeState::~qPlayerRangeState()
{
}

void qPlayerRangeState::Enter()
{
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativeScale(600.f, 600.f, 0.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.22f, 0.22f, 0.f));

	GetOwner()->FlipBookComponent()->Play(20, 15, false);
}

void qPlayerRangeState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"Idle");
	}
}

void qPlayerRangeState::Exit()
{
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
