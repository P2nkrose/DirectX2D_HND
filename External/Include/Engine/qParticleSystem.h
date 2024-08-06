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

public:
	void SetParticleTexture(Ptr<qTexture> _Texture) { m_ParticleTex = _Texture; }

private:
	qStructuredBuffer*			m_ParticleBuffer;
	int							m_MaxParticleCount;
	Ptr<qParticleTickCS>		m_TickCS;

	Ptr<qTexture>				m_ParticleTex;
};

