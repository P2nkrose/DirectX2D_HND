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

	virtual void SaveToFile(FILE* _File) override;   // 파일에 컴포넌트의 정보를 저장
	virtual void LoadFromFile(FILE* _File) override; // 파일에 컴포넌트의 정보를 로드

public:
	void SetParticleTexture(Ptr<qTexture> _Texture) { m_ParticleTex = _Texture; }

private:
	Ptr<qParticleTickCS>		m_TickCS;
	qStructuredBuffer*			m_ParticleBuffer;       // 모든 파티클 정보
	qStructuredBuffer*			m_SpawnCountBuffer;     // 파티클 활성화 숫자 전달용 버퍼

	Ptr<qTexture>				m_ParticleTex;
	float						m_Time;                 // 누적시간

	int							m_MaxParticleCount;
};

