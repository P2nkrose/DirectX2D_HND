#include "pch.h"
#include "qDrownedDeathState.h"

#include <Scripts/qDrownedScript.h>

qDrownedDeathState::qDrownedDeathState()
	: qState((UINT)STATE_TYPE::DROWNEDDEATHSTATE)
{
}

qDrownedDeathState::~qDrownedDeathState()
{
}

void qDrownedDeathState::Enter()
{
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativeScale(241.f, 325.f, 10.f);
	GetOwner()->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	GetOwner()->FlipBookComponent()->Play(5, 10, false);
}

void qDrownedDeathState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		GetOwner()->Destroy();
	}
}

void qDrownedDeathState::Exit()
{
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
