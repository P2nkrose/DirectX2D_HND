#include "pch.h"
#include "qDrownedAttackState.h"

#include <Scripts/qDrownedScript.h>

qDrownedAttackState::qDrownedAttackState()
	: qState((UINT)STATE_TYPE::DROWNEDATTACKSTATE)
{
}

qDrownedAttackState::~qDrownedAttackState()
{
}

void qDrownedAttackState::Enter()
{
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativeScale(270.f, 222.f, 10.f);
	GetOwner()->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	GetOwner()->FlipBookComponent()->Play(3, 10, false);
}

void qDrownedAttackState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"DrownedIdle");
	}
}

void qDrownedAttackState::Exit()
{
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
