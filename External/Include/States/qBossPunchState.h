#pragma once
#include <Engine/qState.h>

class qBossPunchState : public qState
{
public:
	CLONE(qBossPunchState);
	qBossPunchState();
	~qBossPunchState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
};

