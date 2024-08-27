#pragma once
#include <Engine/qState.h>

class qPlayerCombo3State : public qState
{
public:
	CLONE(qPlayerCombo3State);
	qPlayerCombo3State();
	~qPlayerCombo3State();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
};

