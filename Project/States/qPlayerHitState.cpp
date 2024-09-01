#include "pch.h"
#include "qPlayerHitState.h"

#include <Scripts/qPlayerScript.h>

qPlayerHitState::qPlayerHitState()
	: m_HitSpeed(200.f)
{
}

qPlayerHitState::~qPlayerHitState()
{
}

void qPlayerHitState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(11, 15, false);
}

void qPlayerHitState::FinalTick()
{
	qPlayerScript* pPlayerScript = GetOwner()->GetScript<qPlayerScript>();
	Vec3 PlayerPos = GetOwner()->Transform()->GetRelativePos();

	if (pPlayerScript->GetPlayerDir() == DIRECTION::LEFT)
	{
		m_MaxRange += m_HitSpeed * DT;
		PlayerPos += Vec3(0.7f, 0.f, 0.f) * m_HitSpeed * DT;
	}
	else if (pPlayerScript->GetPlayerDir() == DIRECTION::RIGHT)
	{
		m_MaxRange += m_HitSpeed * DT;
		PlayerPos += Vec3(-0.7f, 0.f, 0.f) * m_HitSpeed * DT;
	}

	if (70.f < m_MaxRange)
	{
		m_MaxRange = 0.f;
		//ChangeState(L"RunToIdle");
	}


	GetOwner()->Transform()->SetRelativePos(PlayerPos);




	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"Idle");
	}

}

void qPlayerHitState::Exit()
{
}
