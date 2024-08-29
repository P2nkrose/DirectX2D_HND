#pragma once
#include <Engine/qState.h>

class qPlayerRangeState : public qState
{
public:
	CLONE(qPlayerRangeState);
	qPlayerRangeState();
	~qPlayerRangeState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;

private:
	Vec3		OGScale;
	Vec3		OGColScale;
};

