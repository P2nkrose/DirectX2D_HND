#pragma once
#include <Engine/qState.h>

class qDrownedHitState : public qState
{
public:
	CLONE(qDrownedHitState);
	qDrownedHitState();
	~qDrownedHitState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
};

