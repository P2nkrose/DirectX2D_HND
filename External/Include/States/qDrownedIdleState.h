#pragma once
#include <Engine/qState.h>

class qDrownedIdleState : public qState
{
public:
	CLONE(qDrownedIdleState);
	qDrownedIdleState();
	~qDrownedIdleState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
};

