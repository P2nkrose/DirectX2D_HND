#pragma once
#include <Engine/qScript.h>

class qMissileScript : public qScript
{
public:
	CLONE(qMissileScript);
	qMissileScript();
	~qMissileScript();

	
public:
	virtual void Begin() override;
	virtual void Tick() override;
	virtual void BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider) override;


private:
	float		m_Speed;
};

