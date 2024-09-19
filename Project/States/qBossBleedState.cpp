#include "pch.h"
#include "qBossBleedState.h"

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

#include <Scripts/qBossScript.h>
#include <Scripts/qBleedScript.h>

qBossBleedState::qBossBleedState()
	: qState((UINT)STATE_TYPE::BOSSBLEEDSTATE)
{
}

qBossBleedState::~qBossBleedState()
{
}

void qBossBleedState::Enter()
{
	OGPos = GetOwner()->Transform()->GetRelativePos();
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	qBossScript* BossScript = GetOwner()->GetScript<qBossScript>();
	if (BossScript->GetBossDir() == DIRECTION::LEFT)
	{
		GetOwner()->Transform()->SetRelativePos(OGPos.x - 70.f, OGPos.y + 133.f, OGPos.z);
	}
	else if (BossScript->GetBossDir() == DIRECTION::RIGHT)
	{
		GetOwner()->Transform()->SetRelativePos(OGPos.x + 70.f, OGPos.y + 133.f, OGPos.z);
	}

	GetOwner()->Transform()->SetRelativeScale(700.f, 650.f, 10.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.35f, 0.41f, 0.f));
	GetOwner()->Collider2D()->SetOffset(Vec3(0.f, -0.23f, 0.f));

	GetOwner()->FlipBookComponent()->Play(5, 10, false);
}

void qBossBleedState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"BossIdle");
	}
}

void qBossBleedState::Exit()
{
	GetOwner()->Transform()->SetRelativePos(OGPos);
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
