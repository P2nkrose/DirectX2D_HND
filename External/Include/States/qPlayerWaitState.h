#pragma once
#include <Engine/qState.h>

class qPlayerWaitState : public qState
{
public:
	CLONE(qPlayerWaitState);
	qPlayerWaitState();
	~qPlayerWaitState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
};

