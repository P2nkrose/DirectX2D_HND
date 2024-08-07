#pragma once
#include "qRenderComponent.h"

#include "qParticleTickCS.h"

class qStructuredBuffer;

struct tSpawnCount
{
	UINT    iSpawnCount;
	UINT    padding[3];
};


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
	Ptr<qParticleTickCS>		m_TickCS;
	qStructuredBuffer*			m_ParticleBuffer;       // ��� ��ƼŬ ����
	qStructuredBuffer*			m_SpawnCountBuffer;     // ��ƼŬ Ȱ��ȭ ���� ���޿� ����

	Ptr<qTexture>				m_ParticleTex;
	float						m_Time;                 // �����ð�

	int							m_MaxParticleCount;
};

