#include "pch.h"
#include "qSkeletonIdleState.h"

#include <Scripts/qSkeletonScript.h>


qSkeletonIdleState::qSkeletonIdleState()
	: qState((UINT)STATE_TYPE::SKELETONIDLESTATE)
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
}

void qSkeletonIdleState::Exit()
{
}
