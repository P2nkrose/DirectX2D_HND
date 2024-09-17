#pragma once
#include <Engine/qState.h>

class qBossIdleState : public qState
{
public:
	CLONE(qBossIdleState);
	qBossIdleState();
	~qBossIdleState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
};

