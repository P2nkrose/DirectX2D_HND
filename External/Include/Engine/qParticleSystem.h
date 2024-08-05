#pragma once
#include "qRenderComponent.h"

#include "qParticleTickCS.h"

class qStructuredBuffer;

class qParticleSystem : public qRenderComponent
{
public:
	CLONE(qParticleSystem);
	qParticleSystem();
	~qParticleSystem();


public:
	virtual void FinalTick() override;
	virtual void Render() override;

	virtual void SaveToFile(FILE* _File) override;   // ���Ͽ� ������Ʈ�� ������ ����
	virtual void LoadFromFile(FILE* _File) override; // ���Ͽ� ������Ʈ�� ������ �ε�



private:
	qStructuredBuffer*			m_ParticleBuffer;
	int							m_MaxParticleCount;
	Ptr<qParticleTickCS>		m_TickCS;
};

