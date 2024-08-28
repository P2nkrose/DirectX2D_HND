#include "pch.h"
#include "qPlayerCombo3State.h"

#include <Scripts/qPlayerScript.h>

qPlayerCombo3State::qPlayerCombo3State()
{
}

qPlayerCombo3State::~qPlayerCombo3State()
{
}

void qPlayerCombo3State::Enter()
{
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativeScale(650.f, 650.f, 0.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.2f, 0.2f, 0.f));

	GetOwner()->FlipBookComponent()->Play(15, 15, false);
}

void qPlayerCombo3State::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		if (KEY_TAP(KEY::A))
		{
			ChangeState(L"Combo4");
		}
		else
		{
			ChangeState(L"Idle");
		}
	}
}

void qPlayerCombo3State::Exit()
{
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
