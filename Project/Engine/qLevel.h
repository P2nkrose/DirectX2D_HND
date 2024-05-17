#pragma once
#include "qEntity.h"

class qLayer;
class qGameObject;

class qLevel : public qEntity
{
public:
	virtual qLevel* Clone() { return new qLevel(*this); }
	qLevel();
	~qLevel();

public:
	void Begin();
	void Tick();
	void FinalTick();

public:
	void AddObject(int LayerIdx, qGameObject* _Object);
	qLayer* GetLayer(int _LayerIdx) { return m_Layer[_LayerIdx]; }


private:
	qLayer*		m_Layer[MAX_LAYER];
};

