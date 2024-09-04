#include "pch.h"
#include "qPlayerTeleportState.h"

#include <Engine/qFlipBookComponent.h>
#include <Engine/qGameObject.h>
#include <Scripts/qPlayerScript.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qPlayerTeleportState::qPlayerTeleportState()
{
}

qPlayerTeleportState::~qPlayerTeleportState()
{
}

void qPlayerTeleportState::Enter()
{
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativeScale(299.f, 299.f, 0.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.5f, 0.5f, 0.f));

	GetOwner()->FlipBookComponent()->Play(22, 15, false);
}

void qPlayerTeleportState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		ChangeState(L"TeleportFinish");
	}
}

void qPlayerTeleportState::Exit()
{
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);

	qGameObject* pPost = qLevelMgr::GetInst()->FindObjectByName(L"Post");
	pPost->FSM()->ChangeState(L"PostClose");

	//qLevel* pStage1 = qLevelMgr::GetInst()->GetLevelbyName(L"stage1");
	//qLevel* pStage2 = qLevelMgr::GetInst()->GetLevelbyName(L"stage2");
	//
	//qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	//
	//if (pCurLevel->GetName() == L"stage1")
	//{
	//	ChangeLevel(pStage2, LEVEL_STATE::PLAY);
	//}
	//else if (pCurLevel->GetName() == L"stage2")
	//{
	//	//ChangeLevel(pBoss, LEVEL_STATE::PLAY);
	//}
}
