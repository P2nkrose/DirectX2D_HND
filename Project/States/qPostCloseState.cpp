#include "pch.h"
#include "qPostCloseState.h"

#include <Engine/qFlipBookComponent.h>
#include <Engine/qGameObject.h>
#include <Scripts/qScriptMgr.h>
#include <Scripts/qPlayerScript.h>
#include <Scripts/qPostScript.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qPostCloseState::qPostCloseState()
{
}

qPostCloseState::~qPostCloseState()
{
}

void qPostCloseState::Enter()
{
	qGameObject* pPlayer = qLevelMgr::GetInst()->FindObjectByName(L"Player");
	Vec3 PlayerPos = pPlayer->Transform()->GetRelativePos();


	GetOwner()->Transform()->SetRelativePos(Vec3(474.f, -184.f, 10.f));
	GetOwner()->Transform()->SetRelativeScale(Vec3(1600.f, 900.f, 0.f));

	GetOwner()->FlipBookComponent()->Play(4, 10, false);
}

void qPostCloseState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		qLevel* pStage1 = qLevelMgr::GetInst()->GetLevelbyName(L"stage1");
		qLevel* pStage2 = qLevelMgr::GetInst()->GetLevelbyName(L"stage2");

		qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();

		if (pCurLevel->GetName() == L"stage1")
		{
			ChangeLevel(pStage2, LEVEL_STATE::PLAY);
		}
		else if (pCurLevel->GetName() == L"stage2")
		{
			//ChangeLevel(pBoss, LEVEL_STATE::PLAY);
		}
	}

	
}

void qPostCloseState::Exit()
{


	//qLevel* pStage1 = qLevelMgr::GetInst()->GetLevelbyName(L"stage1");
	//qLevel* pStage2 = qLevelMgr::GetInst()->GetLevelbyName(L"stage2");

	//qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();

	//if (pCurLevel->GetName() == L"stage1")
	//{
	//	ChangeLevel(pStage2, LEVEL_STATE::PLAY);
	//}
	//else if (pCurLevel->GetName() == L"stage2")
	//{
	//	//ChangeLevel(pBoss, LEVEL_STATE::PLAY);
	//}
}
