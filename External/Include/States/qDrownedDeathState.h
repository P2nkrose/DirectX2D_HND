#pragma once
#include <Engine/qState.h>

class qDrownedDeathState : public qState
{
public:
	CLONE(qDrownedDeathState);
	qDrownedDeathState();
	~qDrownedDeathState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
};

