#pragma once
#include <Engine/qState.h>

class qPlayerCombo1State : public qState
{
public:
	CLONE(qPlayerCombo1State);
	qPlayerCombo1State();
	~qPlayerCombo1State();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;


private:
	Vec3		OGScale;
	Vec3		OGColScale;
};

