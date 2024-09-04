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
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativeScale(299.f, 299.f, 0.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.5f, 0.5f, 0.f));

	GetOwner()->FlipBookComponent()->Play(23, 15, false);
}

void qPlayerTeleportFinishState::FinalTick()
{
}

void qPlayerTeleportFinishState::Exit()
{
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
