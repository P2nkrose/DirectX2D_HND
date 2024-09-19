#include "pch.h"
#include "qBossDeathState.h"

#include <Scripts/qBossScript.h>

qBossDeathState::qBossDeathState()
	: qState((UINT)STATE_TYPE::BOSSDEATHSTATE)
{
}

qBossDeathState::~qBossDeathState()
{
}

void qBossDeathState::Enter()
{
	OGPos = GetOwner()->Transform()->GetRelativePos();
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativePos(OGPos.x, OGPos.y + 58.f, OGPos.z);
	GetOwner()->Transform()->SetRelativeScale(690.f, 480.f, 10.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.0f, 0.0f, 0.f));

	GetOwner()->FlipBookComponent()->Play(7, 10, false);
}

void qBossDeathState::FinalTick()
{
	static bool flag = false;

	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished() && !flag)
	{
		// ���� ��ŹŹ (�ð�������)



	}
}

void qBossDeathState::Exit()
{
	GetOwner()->Transform()->SetRelativePos(OGPos);
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
