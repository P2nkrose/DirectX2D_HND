#include "pch.h"
#include "qBossSlamState.h"

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

#include <Scripts/qBossScript.h>
#include <Scripts/qSlamScript.h>


qBossSlamState::qBossSlamState()
	: qState((UINT)STATE_TYPE::BOSSSLAMSTATE)
{
}

qBossSlamState::~qBossSlamState()
{
}

void qBossSlamState::Enter()
{
	OGPos = GetOwner()->Transform()->GetRelativePos();
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativePos(OGPos.x, OGPos.y + 127.f, OGPos.z);
	GetOwner()->Transform()->SetRelativeScale(500.f, 600.f, 10.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.5f, 0.45f, 0.f));
	GetOwner()->Collider2D()->SetOffset(Vec3(0.13f, -0.24f, 0.f));

	GetOwner()->FlipBookComponent()->Play(4, 10, true);
}

void qBossSlamState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"BossIdle");
	}
}

void qBossSlamState::Exit()
{
	GetOwner()->Transform()->SetRelativePos(OGPos);
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
