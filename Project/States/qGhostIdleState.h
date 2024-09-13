#pragma once
#include <Engine/qState.h>

class qGameObject;

class qGhostIdleState : public qState
{
public:
	CLONE(qGhostIdleState);
	qGhostIdleState();
	~qGhostIdleState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;


private:
	float			m_DetectRange;
	float			m_AttackRange;
};

