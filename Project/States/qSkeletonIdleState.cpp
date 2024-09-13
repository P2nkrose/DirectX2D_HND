#include "pch.h"
#include "qSkeletonIdleState.h"

#include <Scripts/qSkeletonScript.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>


qSkeletonIdleState::qSkeletonIdleState()
	: qState((UINT)STATE_TYPE::SKELETONIDLESTATE)
	, m_DetectRange(220.f)
{
}

qSkeletonIdleState::~qSkeletonIdleState()
{
}

void qSkeletonIdleState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(0, 10, true);
}

void qSkeletonIdleState::FinalTick()
{
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	qGameObject* Player = pCurLevel->FindObjectByName(L"Player");

	Vec3 SkeletonPos = GetOwner()->Transform()->GetRelativePos();
	Vec3 PlayerPos = Player->Transform()->GetRelativePos();

	Vec3 Dir = PlayerPos - SkeletonPos;

	float Dist = Dir.Length();

	static bool flag = false;

	if (Dist < m_DetectRange && !flag)
	{
		// 느낌표 생성


		flag = true;
	}


	if (Dist < m_DetectRange)
	{
		DIRECTION CurDir = GetOwner()->GetScript<qSkeletonScript>()->GetSkeletonDir();

		// 같은 방향
		if (Dir.x * (int)CurDir > 0)
		{
			ChangeState(L"SkeletonAttack");
		}
	}


}

void qSkeletonIdleState::Exit()
{
}
