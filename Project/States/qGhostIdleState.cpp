#include "pch.h"
#include "qGhostIdleState.h"

#include <Scripts/qGhostScript.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qGhostIdleState::qGhostIdleState()
	: qState((UINT)STATE_TYPE::GHOSTIDLESTATE)
	, m_DetectRange(600.f)
	, m_AttackRange(200.f)
{
}

qGhostIdleState::~qGhostIdleState()
{
}

void qGhostIdleState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(0, 10, true);
}

void qGhostIdleState::FinalTick()
{
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	qGameObject* Player = pCurLevel->FindObjectByName(L"Player");

	Vec3 GhostPos = GetOwner()->Transform()->GetRelativePos();
	Vec3 PlayerPos = Player->Transform()->GetRelativePos();

	Vec3 Dir = PlayerPos - GhostPos;

	float Dist = Dir.Length();

	static bool flag = false;

	if (Dist < m_DetectRange && !flag)
	{
		// 느낌표 생성


		flag = true;
	}


	if (Dist < m_DetectRange)
	{
		DIRECTION CurDir = GetOwner()->GetScript<qGhostScript>()->GetGhostDir();

		// 같은 방향
		if (Dir.x * (int)CurDir > 0)
		{
			ChangeState(L"GhostRun");
		}
		else
		{
			ChangeState(L"GhostUturn");
		}
	}

	if (Dist < m_AttackRange)
	{
		DIRECTION CurDir = GetOwner()->GetScript<qGhostScript>()->GetGhostDir();

		// 같은 방향
		if (Dir.x * (int)CurDir > 0)
		{
			ChangeState(L"GhostAttack");
		}
		else
		{
			ChangeState(L"GhostUturn");
		}
	}
}

void qGhostIdleState::Exit()
{
}
