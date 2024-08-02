#pragma once
#include "qRenderComponent.h"

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

	virtual void SaveToFile(FILE* _File) override;   // 파일에 컴포넌트의 정보를 저장
	virtual void LoadFromFile(FILE* _File) override; // 파일에 컴포넌트의 정보를 로드



private:
	qStructuredBuffer*			m_ParticleBuffer;

	int							m_MaxParticleCount;
};

