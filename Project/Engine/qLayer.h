#pragma once
#include "qEntity.h"

class qGameObject;

class qLayer : public qEntity
{
public:
	virtual qLayer* Clone() { return new qLayer(*this); }
	qLayer(int _LayerIdx);
	~qLayer();

public:
	
	void Begin();
	void Tick();
	void FinalTick();
	void Render();

public:
	void AddObject(qGameObject* _Object) { m_Parents.push_back(_Object); }

private:
	vector<qGameObject*>	m_Parents;
	const int				m_LayerIdx;
};

