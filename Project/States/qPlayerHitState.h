#pragma once
#include <Engine/qState.h>

class qPlayerHitState : public qState
{
public:
	CLONE(qPlayerHitState);
	qPlayerHitState();
	~qPlayerHitState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;


private:
	float		m_HitSpeed;
	float		m_MaxRange;
};

