#include "pch.h"
#include "qParticleSystem.h"

#include "qDevice.h"
#include "qStructuredBuffer.h"


qParticleSystem::qParticleSystem()
	: qRenderComponent(COMPONENT_TYPE::PARTICLESYSTEM)
	, m_ParticleBuffer(nullptr)
	, m_MaxParticleCount(100)
{
	tParticle Particle = {};
	Particle.Active = true;
	Particle.vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	m_ParticleBuffer = new qStructuredBuffer;
	m_ParticleBuffer->Create(sizeof(tParticle), m_MaxParticleCount, SB_TYPE::SRV_UAV, false, &Particle);

	tParticle Particle2 = {};
	m_ParticleBuffer->GetData(&Particle2);
}

qParticleSystem::~qParticleSystem()
{
	if (nullptr != m_ParticleBuffer)
		delete m_ParticleBuffer;
}

void qParticleSystem::FinalTick()
{
}

void qParticleSystem::Render()
{
}

void qParticleSystem::SaveToFile(FILE* _File)
{
}

void qParticleSystem::LoadFromFile(FILE* _File)
{
}
