#include "pch.h"
#include "qLoadingState.h"

#include <Engine/qFlipBookComponent.h>
#include <Engine/qGameObject.h>
#include <Scripts/qScriptMgr.h>
#include <Scripts/qPostScript.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qLoadingState::qLoadingState()
	: qState((UINT)STATE_TYPE::LOADINGSTATE)
{
}

qLoadingState::~qLoadingState()
{
}

void qLoadingState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(1, 10, false);
}

void qLoadingState::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		qLevel* pStage1 = qLevelMgr::GetInst()->GetLevelbyName(L"stage1");
		
		ChangeLevel(pStage1, LEVEL_STATE::PLAY);
	}
}

void qLoadingState::Exit()
{
}
