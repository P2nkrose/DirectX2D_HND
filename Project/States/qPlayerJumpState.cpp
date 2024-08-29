#include "pch.h"
#include "qPlayerJumpState.h"

#include <Scripts/qPlayerScript.h>

qPlayerJumpState::qPlayerJumpState()
{
}

qPlayerJumpState::~qPlayerJumpState()
{
}

void qPlayerJumpState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(7, 15, false);
}

void qPlayerJumpState::FinalTick()
{
	qPlayerScript* pPlayerScript = GetOwner()->GetScript<qPlayerScript>();

	if (KEY_RELEASED(KEY::SPACE))
	{
		ChangeState(L"Falling");
	}

	if (GetOwner()->RigidBody()->IsGround())
	{
		ChangeState(L"Landing");
	}

	if (KEY_TAP(KEY::LSHIFT) && !(pPlayerScript->IsDashCoolTime()))
	{
		ChangeState(L"Dash");
	}

}

void qPlayerJumpState::Exit()
{
}
