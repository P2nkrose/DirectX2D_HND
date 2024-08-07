#pragma once
#include "qComputeShader.h"

class qStructuredBuffer;

class qParticleTickCS : public qComputeShader
{
public:
	qParticleTickCS();
	~qParticleTickCS();

public:
	virtual int Binding() override;
	virtual void CalcGroupNum() override;
	virtual void Clear() override;

public:
	void SetParticleBuffer(qStructuredBuffer* _Buffer) { m_ParticleBuffer = _Buffer; }
	void SetSpawnCount(qStructuredBuffer* _Buffer) { m_SpawnCountBuffer = _Buffer; }

private:
	qStructuredBuffer*		m_ParticleBuffer;
	qStructuredBuffer*		m_SpawnCountBuffer;

};

