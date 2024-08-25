#include "pch.h"
#include "qPlayerIdleState.h"


#include <Scripts/qPlayerScript.h>

qPlayerIdleState::qPlayerIdleState()
{
	
}

qPlayerIdleState::~qPlayerIdleState()
{

}

void qPlayerIdleState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(0, 15, true);
}



void qPlayerIdleState::FinalTick()
{
	qPlayerScript* pPlayerScript = GetOwner()->GetScript<qPlayerScript>();

	if (KEY_TAP(KEY::LEFT) || KEY_PRESSED(KEY::LEFT))
	{
		if (pPlayerScript->IsDirChanged())
		{
			ChangeState(L"IdleUTurn");
		}
		else
		{
			ChangeState(L"IdleToRun");
		}
	}

	if (KEY_TAP(KEY::RIGHT) || KEY_PRESSED(KEY::RIGHT))
	{
		if (pPlayerScript->IsDirChanged())
		{
			ChangeState(L"IdleUTurn");
		}
		else
		{
			ChangeState(L"IdleToRun");
		}
	}


}



void qPlayerIdleState::Exit()
{
}
