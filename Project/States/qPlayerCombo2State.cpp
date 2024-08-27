#include "pch.h"
#include "qPlayerCombo2State.h"

#include <Scripts/qPlayerScript.h>

qPlayerCombo2State::qPlayerCombo2State()
{
}

qPlayerCombo2State::~qPlayerCombo2State()
{
}

void qPlayerCombo2State::Enter()
{
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativeScale(232.f, 208.f, 0.f);
	GetOwner()->Collider2D()->SetScale(Vec3(1.0f, 1.0f, 0.f));

	GetOwner()->FlipBookComponent()->Play(15, 10, false);
}

void qPlayerCombo2State::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		if (KEY_TAP(KEY::A))
		{
			ChangeState(L"Combo3");
		}
		else
		{
			ChangeState(L"Idle");
		}
	}
}

void qPlayerCombo2State::Exit()
{
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
