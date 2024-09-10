#include "pch.h"
#include "qSkeletonDeathState.h"

#include <Scripts/qSkeletonScript.h>

qSkeletonDeathState::qSkeletonDeathState()
	: qState((UINT)STATE_TYPE::SKELETONDEATHSTATE)
{
}

qSkeletonDeathState::~qSkeletonDeathState()
{
}

void qSkeletonDeathState::Enter()
{
	OGPos = GetOwner()->Transform()->GetRelativePos();
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativePos(-3244.f, -370.f, 10.f);
	GetOwner()->Transform()->SetRelativeScale(260.f, 200.f, 0.f);
	//GetOwner()->Collider2D()->SetScale(Vec3(0.5f, 1.0f, 0.f));

	GetOwner()->FlipBookComponent()->Play(2, 20, false);
}

void qSkeletonDeathState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		GetOwner()->Destroy();
	}
}

void qSkeletonDeathState::Exit()
{
	
}
