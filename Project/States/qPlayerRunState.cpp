#include "pch.h"
#include "qPlayerRunState.h"

#include <Scripts/qPlayerScript.h>

qPlayerRunState::qPlayerRunState()
{
}

qPlayerRunState::~qPlayerRunState()
{

}

void qPlayerRunState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(2, 20, true);
}


void qPlayerRunState::FinalTick()
{
	qPlayerScript* pPlayerScript = GetOwner()->GetScript<qPlayerScript>();

	if (KEY_RELEASED(KEY::LEFT) || KEY_RELEASED(KEY::RIGHT))
	{
		ChangeState(L"RunToIdle");
	}

	if (pPlayerScript->IsDirChanged())
	{
		ChangeState(L"RunUTurn");
	}

	if (KEY_TAP(KEY::SPACE))
	{
		ChangeState(L"Jump");
	}

	if (KEY_TAP(KEY::LSHIFT) && !(pPlayerScript->IsDashCoolTime()))
	{
		ChangeState(L"Dash");
	}
}


void qPlayerRunState::Exit()
{
}