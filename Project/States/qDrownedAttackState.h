#pragma once
#include <Engine/qState.h>

class qDrownedAttackState : public qState
{
public:
	CLONE(qDrownedAttackState);
	qDrownedAttackState();
	~qDrownedAttackState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;


private:
	Vec3			OGScale;
	Vec3			OGColScale;
};

