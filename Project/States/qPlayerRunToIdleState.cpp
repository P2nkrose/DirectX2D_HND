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
	GetOwner()->FlipBookComponent()->Play(4, 20, true);
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

	// �ִϸ��̼��� ���� �Ǿ��ٸ�
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"Idle");
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

void qPlayerRunToIdleState::Exit()
{
}