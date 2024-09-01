#include "pch.h"
#include "qPlayerKrushState.h"

#include <Scripts/qPlayerScript.h>

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qPlayerKrushState::qPlayerKrushState()
	: m_KrushSpeed(1200.f)
{
}

qPlayerKrushState::~qPlayerKrushState()
{
}

void qPlayerKrushState::Enter()
{
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativeScale(700.f, 700.f, 0.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.19f, 0.19f, 0.f));

	GetOwner()->FlipBookComponent()->Play(21, 15, false);
}

void qPlayerKrushState::FinalTick()
{
	qPlayerScript* pPlayerScript = GetOwner()->GetScript<qPlayerScript>();

	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();

	if (pCurLevel->GetName() == L"stage1")
	{
		Vec3 PlayerPos = GetOwner()->Transform()->GetRelativePos();

		if (PlayerPos.y <= -420.f)
		{
			PlayerPos.y = -420.f;
		}
		else
		{
			PlayerPos += Vec3(0.f, -1.2f, 0.f) * m_KrushSpeed * DT;
		}

		GetOwner()->Transform()->SetRelativePos(PlayerPos);
	}



	if (pPlayerScript->RigidBody()->IsGround() && GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"Idle");
	}

}

void qPlayerKrushState::Exit()
{
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
