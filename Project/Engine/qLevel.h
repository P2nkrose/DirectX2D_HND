#pragma once
#include "qEntity.h"

class qLayer;

class qLevel : public qEntity
{
public:
	virtual qLevel* Clone() { return new qLevel(*this); }
	qLevel();
	~qLevel();

public:
	void Tick();
	void FinalTick();
	void Render();


private:
	qLayer* m_Layer[MAX_LAYER];
};

