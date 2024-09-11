#include "pch.h"
#include "qPlayerBumpState.h"

#include <Scripts/qPlayerScript.h>

qPlayerBumpState::qPlayerBumpState()
	: qState((UINT)STATE_TYPE::PLAYERBUMPSTATE)
	, m_BumpSpeed(200.f)
	, m_MaxRange(0.f)
{
}

qPlayerBumpState::~qPlayerBumpState()
{
}

void qPlayerBumpState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(24, 15, false);
}

void qPlayerBumpState::FinalTick()
{
	qPlayerScript* pPlayerScript = GetOwner()->GetScript<qPlayerScript>();
	Vec3 PlayerPos = GetOwner()->Transform()->GetRelativePos();

	if (pPlayerScript->GetPlayerDir() == DIRECTION::LEFT)
	{
		m_MaxRange += m_BumpSpeed * DT;
		PlayerPos += Vec3(0.7f, 0.f, 0.f) * m_BumpSpeed * DT;
	}
	else if (pPlayerScript->GetPlayerDir() == DIRECTION::RIGHT)
	{
		m_MaxRange += m_BumpSpeed * DT;
		PlayerPos += Vec3(-0.7f, 0.f, 0.f) * m_BumpSpeed * DT;
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

void qPlayerBumpState::Exit()
{
}
