#pragma once
#include <Engine/qState.h>

class qPlayerCombo1EndState : public qState
{
public:
	CLONE(qPlayerCombo1EndState);
	qPlayerCombo1EndState();
	~qPlayerCombo1EndState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
};

