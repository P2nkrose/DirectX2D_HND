#pragma once
#include <Engine/qState.h>

class qDrownedRunState : public qState
{
public:
	CLONE(qDrownedRunState);
	qDrownedRunState();
	~qDrownedRunState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
};

