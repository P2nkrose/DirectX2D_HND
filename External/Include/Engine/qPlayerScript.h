#pragma once
#include "qScript.h"

class qPlayerScript : public qScript
{
public:
	CLONE(qPlayerScript);
	qPlayerScript();
	~qPlayerScript();

public:
	virtual void Tick() override;


private:
	float		m_Speed;
};

