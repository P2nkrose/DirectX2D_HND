#include "pch.h"
#include "qPostOpenState.h"

#include <Engine/qFlipBookComponent.h>
#include <Engine/qGameObject.h>
#include <Scripts/qScriptMgr.h>
#include <Scripts/qPlayerScript.h>
#include <Scripts/qPostScript.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qPostOpenState::qPostOpenState()
{
}

qPostOpenState::~qPostOpenState()
{
}

void qPostOpenState::Enter()
{
	GetOwner()->Transform()->SetRelativePos(Vec3(-4910.f, -40.f, 10.f));
	GetOwner()->Transform()->SetRelativeScale(Vec3(1600.f, 900.f, 0.f));

	GetOwner()->FlipBookComponent()->Play(5, 20, false);
}

void qPostOpenState::FinalTick()
{
	static bool flag = false;

	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished() && !flag)
	{
		GetOwner()->Destroy();




	
		flag = true;
	}
}

void qPostOpenState::Exit()
{
}
