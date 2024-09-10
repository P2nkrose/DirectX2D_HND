#include "pch.h"
#include "qSkeletonAttackState.h"

#include <Scripts/qSkeletonScript.h>

qSkeletonAttackState::qSkeletonAttackState()
	: qState((UINT)STATE_TYPE::SKELETONATTACKSTATE)
	, SkeletonAttackHitBox(nullptr)
{
}

qSkeletonAttackState::~qSkeletonAttackState()
{
}

void qSkeletonAttackState::Enter()
{
	OGPos = GetOwner()->Transform()->GetRelativePos();
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();
	//OGColOffset = GetOwner()->Collider2D()->GetOffset();

	GetOwner()->Transform()->SetRelativePos(-3220.f, -395.f, 10.f);
	GetOwner()->Transform()->SetRelativeScale(340.f, 160.f, 0.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.5f, 1.0f, 0.f));
	//GetOwner()->Collider2D()->SetOffset(Vec3(-15.f, 5.f, 0.f));

	GetOwner()->FlipBookComponent()->Play(1, 15, false);
}

void qSkeletonAttackState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"SkeletonIdle");
	}
}

void qSkeletonAttackState::Exit()
{
	GetOwner()->Transform()->SetRelativePos(OGPos);
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
	//GetOwner()->Collider2D()->SetOffset(OGColOffset);
}
