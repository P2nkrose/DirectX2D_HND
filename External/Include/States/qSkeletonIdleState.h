#pragma once
#include <Engine/qState.h>

class qSkeletonIdleState : public qState
{
public:
	CLONE(qSkeletonIdleState);
	qSkeletonIdleState();
	~qSkeletonIdleState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;


private:
	float		m_DetectRange;
};

