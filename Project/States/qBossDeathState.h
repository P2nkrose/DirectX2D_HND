#pragma once
#include <Engine/qState.h>

class qBossDeathState : public qState
{
public:
	CLONE(qBossDeathState);
	qBossDeathState();
	~qBossDeathState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
};

