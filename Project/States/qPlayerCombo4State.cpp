#include "pch.h"
#include "qPlayerCombo4State.h"

#include <Scripts/qPlayerScript.h>

qPlayerCombo4State::qPlayerCombo4State()
{
}

qPlayerCombo4State::~qPlayerCombo4State()
{
}

void qPlayerCombo4State::Enter()
{
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativeScale(700.f, 700.f, 0.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.187f, 0.187f, 0.f));

	GetOwner()->FlipBookComponent()->Play(16, 15, false);
}

void qPlayerCombo4State::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"Idle");
	}
}

void qPlayerCombo4State::Exit()
{
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
