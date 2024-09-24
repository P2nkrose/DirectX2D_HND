#include "pch.h"
#include "qLoading1State.h"

#include <Engine/qFlipBookComponent.h>
#include <Engine/qGameObject.h>
#include <Scripts/qScriptMgr.h>
#include <Scripts/qPostScript.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qLoading1State::qLoading1State()
	: qState((UINT)STATE_TYPE::LOADING1STATE)
{
}

qLoading1State::~qLoading1State()
{
}

void qLoading1State::Enter()
{
	GetOwner()->FlipBookComponent()->Play(1, 10, false);
}

void qLoading1State::FinalTick()
{
	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		qLevel* pStageTitle = qLevelMgr::GetInst()->GetLevelbyName(L"title");

		ChangeLevel(pStageTitle, LEVEL_STATE::PLAY);
	}
}

void qLoading1State::Exit()
{
}
