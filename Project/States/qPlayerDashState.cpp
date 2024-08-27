#include "pch.h"
#include "qPlayerDashState.h"

#include <Scripts/qPlayerScript.h>

qPlayerDashState::qPlayerDashState()
{
	
}

qPlayerDashState::~qPlayerDashState()
{
}

void qPlayerDashState::Enter()
{
	qPlayerScript* pPlayerScript = GetOwner()->GetScript<qPlayerScript>();


	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativeScale(350.f, 350.f, 0.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.37f, 0.37f, 0.f));

	GetOwner()->FlipBookComponent()->Play(10, 10, false);
	
}

void qPlayerDashState::FinalTick()
{
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
