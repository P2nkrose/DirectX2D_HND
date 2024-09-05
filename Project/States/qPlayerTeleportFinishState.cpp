#include "pch.h"
#include "qPlayerTeleportFinishState.h"

#include <Engine/qFlipBookComponent.h>
#include <Engine/qGameObject.h>
#include <Scripts/qPlayerScript.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qPlayerTeleportFinishState::qPlayerTeleportFinishState()
{
}

qPlayerTeleportFinishState::~qPlayerTeleportFinishState()
{
}

void qPlayerTeleportFinishState::Enter()
{
	OGPos = GetOwner()->Transform()->GetRelativePos();
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	//OGColScale = GetOwner()->Collider2D()->GetScale();

	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	if (pCurLevel->GetName() == L"stage1")
	{
		GetOwner()->Transform()->SetRelativePos(875.f, -484.f, 10.f);
		GetOwner()->Transform()->SetRelativeScale(0.01f, 0.01f, 0.f);
	}
	if (pCurLevel->GetName() == L"stage2")
	{
		GetOwner()->RigidBody()->SetGround(true);
		GetOwner()->Transform()->SetRelativePos(-4910.f, -200.f, 10.f);
		GetOwner()->Transform()->SetRelativeScale(0.01f, 0.01f, 0.f);
	}

	
	//GetOwner()->Collider2D()->SetScale(Vec3(0.5f, 0.5f, 0.f));

	GetOwner()->FlipBookComponent()->Play(23, 15, false);

}

void qPlayerTeleportFinishState::FinalTick()
{
	//static bool flag = false;

	//if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished() && !flag)
	//{
	//	for (size_t i = 0; i < GetOwner()->GetChildren().size(); ++i)
	//	{
	//		GetOwner()->GetChildren()[i]->Destroy();
	//	}
	//	GetOwner()->Destroy();

	//	flag = true;
	//}
}

void qPlayerTeleportFinishState::Exit()
{
	GetOwner()->Transform()->SetRelativePos(OGPos);
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	//GetOwner()->Collider2D()->SetScale(OGColScale);
}
