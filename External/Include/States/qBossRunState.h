#pragma once
#include <Engine/qState.h>

class qBossRunState : public qState
{
public:
	CLONE(qBossRunState);
	qBossRunState();
	~qBossRunState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
};

