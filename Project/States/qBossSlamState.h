#pragma once
#include <Engine/qState.h>

class qBossSlamState : public qState
{
public:
	CLONE(qBossSlamState);
	qBossSlamState();
	~qBossSlamState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
};

