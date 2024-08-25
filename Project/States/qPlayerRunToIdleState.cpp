#include "pch.h"
#include "qPlayerRunToIdleState.h"

#include <Scripts/qPlayerScript.h>

qPlayerRunToIdleState::qPlayerRunToIdleState()
{
}

qPlayerRunToIdleState::~qPlayerRunToIdleState()
{
}

void qPlayerRunToIdleState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(4, 15, true);
}

void qPlayerRunToIdleState::FinalTick()
{
	qPlayerScript* pPlayerScript = GetOwner()->GetScript<qPlayerScript>();
	
	if (KEY_TAP(KEY::LEFT) || KEY_PRESSED(KEY::LEFT) || KEY_TAP(KEY::RIGHT) || KEY_PRESSED(KEY::RIGHT))
	{
		if (pPlayerScript->IsDirChanged())
		{
			ChangeState(L"IdleUTurn");
		}
		else
		{
			ChangeState(L"Run");
		}
	}

	// 애니메이션이 종료 되었다면
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"Idle");
	}

}

void qPlayerRunToIdleState::Exit()
{
}
