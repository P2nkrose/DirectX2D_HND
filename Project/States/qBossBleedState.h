#pragma once
#include <Engine/qState.h>

class qBossBleedState : public qState
{
public:
	CLONE(qBossBleedState);
	qBossBleedState();
	~qBossBleedState();


public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;


private:
	qGameObject*		BleedHitbox;
	Vec3				OGPos;
	Vec3				OGScale;
	Vec3				OGColScale;

	bool				HitboxFlag;
};

