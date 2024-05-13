#pragma once
#include "qEntity.h"

class qGameObject;

class qLayer : public qEntity
{
public:
	qLayer();
	~qLayer();

public:
	virtual qLayer* Clone() { return new qLayer(*this); }
	
	void Tick();
	void FinalTick();
	void Render();

private:
	vector<qGameObject*>	m_Parents;
};

