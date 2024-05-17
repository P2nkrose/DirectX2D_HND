#pragma once
#include "qComponent.h"

class qCamera : public qComponent
{
public:
	CLONE(qCamera);
	qCamera();
	~qCamera();

public:
	virtual void Begin() override;
	virtual void FinalTick() override;
	void Render();

public:
	void SetPriority(int _Priority) { m_Priority = _Priority; }


private:
	int			m_Priority;		// 우선순위

	Matrix		m_matView;
	
};

