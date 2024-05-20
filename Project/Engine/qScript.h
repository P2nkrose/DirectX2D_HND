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
};

