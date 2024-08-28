#include "pch.h"
#include "qPlayerCombo1State.h"

#include <Scripts/qPlayerScript.h>

qPlayerCombo1State::qPlayerCombo1State()
{
}

qPlayerCombo1State::~qPlayerCombo1State()
{
}

void qPlayerCombo1State::Enter()
{
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativeScale(550.f, 550.f, 0.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.24f, 0.24f, 0.f));

	GetOwner()->FlipBookComponent()->Play(13, 15, false);
}

void qPlayerCombo1State::FinalTick()
{


	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		if (KEY_TAP(KEY::A))
		{
			ChangeState(L"Combo2");
		}
		else
		{
			ChangeState(L"Idle");
		}
	}
}

void qPlayerCombo1State::Exit()
{
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
