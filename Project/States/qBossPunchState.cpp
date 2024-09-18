#include "pch.h"
#include "qBossPunchState.h"

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

#include <Scripts/qBossScript.h>
#include <Scripts/qPunchScript.h>

qBossPunchState::qBossPunchState()
	: qState((UINT)STATE_TYPE::BOSSPUNCHSTATE)
	, PunchHitbox(nullptr)
{
}

qBossPunchState::~qBossPunchState()
{
}

void qBossPunchState::Enter()
{
	OGPos = GetOwner()->Transform()->GetRelativePos();
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativePos(OGPos.x, OGPos.y + 16.f, OGPos.z);
	GetOwner()->Transform()->SetRelativeScale(1500.f, 370.f, 10.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.16f, 0.72f, 1.f));
	GetOwner()->Collider2D()->SetOffset(Vec3(0.f, -0.09f, 0.f));

	GetOwner()->FlipBookComponent()->Play(3, 20, true);
}

void qBossPunchState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"BossIdle");
	}
}

void qBossPunchState::Exit()
{
	GetOwner()->Transform()->SetRelativePos(OGPos);
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
