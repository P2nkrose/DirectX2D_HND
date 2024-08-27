#include "pch.h"
#include "qPlayerDashState.h"

#include <Scripts/qPlayerScript.h>

qPlayerDashState::qPlayerDashState()
	: m_DashSpeed(800.f)
{
	
}

qPlayerDashState::~qPlayerDashState()
{
}

void qPlayerDashState::Enter()
{	
	OGPos = GetOwner()->Transform()->GetRelativePos();
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativeScale(350.f, 350.f, 0.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.37f, 0.37f, 0.f));

	GetOwner()->FlipBookComponent()->Play(10, 10, false);
	
}

void qPlayerDashState::FinalTick()
{
	qPlayerScript* pPlayerScript = GetOwner()->GetScript<qPlayerScript>();
	Vec3 PlayerPos = GetOwner()->Transform()->GetRelativePos();

	if (KEY_PRESSED(KEY::LSHIFT))
	{
		if (pPlayerScript->GetPlayerDir() == DIRECTION::LEFT)
		{
			m_MaxRange += m_DashSpeed * DT;
			PlayerPos += Vec3(-1.f, 0.f, 0.f) * m_DashSpeed * DT;
		}
		else if (pPlayerScript->GetPlayerDir() == DIRECTION::RIGHT)
		{
			m_MaxRange += m_DashSpeed * DT;
			PlayerPos += Vec3(1.f, 0.f, 0.f) * m_DashSpeed * DT;
		}

		if (350.f < m_MaxRange)
		{
			m_MaxRange = 0.f;
			//ChangeState(L"RunToIdle");
		}
		
	}

	GetOwner()->Transform()->SetRelativePos(PlayerPos);





	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		if (GetOwner()->RigidBody()->IsGround())
		{
			if (KEY_TAP(KEY::SPACE))
			{
				ChangeState(L"Jump");
			}
			else
			{
				ChangeState(L"RunToIdle");
			}
		}
		else
		{
			ChangeState(L"Falling");
		}
	}
}

void qPlayerDashState::Exit()
{
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
