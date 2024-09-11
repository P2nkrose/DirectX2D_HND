#include "pch.h"
#include "qDrownedHitState.h"

#include <Scripts/qDrownedScript.h>

qDrownedHitState::qDrownedHitState()
	: qState((UINT)STATE_TYPE::DROWNEDHITSTATE)
{
}

qDrownedHitState::~qDrownedHitState()
{
}

void qDrownedHitState::Enter()
{
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativeScale(212.f, 251.f, 10.f);
	GetOwner()->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	GetOwner()->FlipBookComponent()->Play(4, 10, false);
}

void qDrownedHitState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"DrownedIdle");
	}
}

void qDrownedHitState::Exit()
{
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
