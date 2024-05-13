#pragma once
#include "qEntity.h"


class qGameObject : public qEntity
{
public:
	virtual qGameObject* Clone() { return new qGameObject(*this); }
	qGameObject();
	~qGameObject();

public:
	void Tick();
	void FinalTick();
	void Render();

private:

};

