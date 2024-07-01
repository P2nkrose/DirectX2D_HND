#pragma once
#include "qComponent.h"

#include "qTimeMgr.h"
#include "qKeyMgr.h"
#include "qAssetMgr.h"
#include "components.h"

class qScript : public qComponent
{
public:
	qScript();
	~qScript();

	virtual void Tick() PURE;
	virtual void FinalTick() final override {}

	virtual void BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider){}
	virtual void Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider){}
	virtual void EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider){}

public:
	qRenderComponent* GetRenderComponent() { return GetOwner()->GetRenderComponent(); }

};

