#include "pch.h"
#include "qPlayerFallingState.h"

#include <Scripts/qPlayerScript.h>

qPlayerFallingState::qPlayerFallingState()
{
}

qPlayerFallingState::~qPlayerFallingState()
{
}

void qPlayerFallingState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(8, 10, true);
}

void qPlayerFallingState::FinalTick()
{
	qPlayerScript* pPlayerScript = GetOwner()->GetScript<qPlayerScript>();

	if (KEY_TAP(KEY::SPACE))
	{
		ChangeState(L"Jump");
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

void qPlayerFallingState::Exit()
{
}
