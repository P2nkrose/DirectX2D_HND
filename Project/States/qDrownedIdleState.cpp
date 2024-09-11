#include "pch.h"
#include "qDrownedIdleState.h"

#include <Scripts/qDrownedScript.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qDrownedIdleState::qDrownedIdleState()
	: qState((UINT)STATE_TYPE::DROWNEDIDLESTATE)
	, m_DetectRange(600.f)
	, m_AttackRange(200.f)
{
}

qDrownedIdleState::~qDrownedIdleState()
{
}

void qDrownedIdleState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(0, 10, true);

}

void qDrownedIdleState::FinalTick()
{
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	qGameObject* Player = pCurLevel->FindObjectByName(L"Player");

	Vec3 DrownedPos = GetOwner()->Transform()->GetRelativePos();
	Vec3 PlayerPos = Player->Transform()->GetRelativePos();
	
	Vec3 Dir = PlayerPos - DrownedPos;

	float Dist = Dir.Length();

	static bool flag = false;

	if (Dist < m_DetectRange && !flag)
	{
		// 느낌표 생성


		flag = true;
	}


	if (Dist < m_DetectRange)
	{
		DIRECTION CurDir = GetOwner()->GetScript<qDrownedScript>()->GetDrownedDir();

		// 같은 방향
		if (Dir.x * (int)CurDir > 0)
		{
			ChangeState(L"DrownedRun");
		}
		else
		{
			ChangeState(L"DrownedUturn");
		}
	}

	if (Dist < m_AttackRange)
	{
		DIRECTION CurDir = GetOwner()->GetScript<qDrownedScript>()->GetDrownedDir();

		// 같은 방향
		if (Dir.x * (int)CurDir > 0)
		{
			ChangeState(L"DrownedAttack");
		}
		else
		{
			ChangeState(L"DrownedUturn");
		}
	}
}

void qDrownedIdleState::Exit()
{
}
