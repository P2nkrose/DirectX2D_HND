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
	GetOwner()->FlipBookComponent()->Play(2, 15, true);
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
}


void qPlayerRunState::Exit()
{
}
