#include "pch.h"
#include "qParticleSystem.h"

#include "qDevice.h"
#include "qAssetMgr.h"
#include "qStructuredBuffer.h"

#include "qTransform.h"


qParticleSystem::qParticleSystem()
	: qRenderComponent(COMPONENT_TYPE::PARTICLESYSTEM)
	, m_ParticleBuffer(nullptr)
	, m_MaxParticleCount(100)
{
	// Mesh / Material
	SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	SetMaterial(qAssetMgr::GetInst()->FindAsset<qMaterial>(L"ParticleRenderMtrl"));

	// ParticleTick ComputeShader
	m_TickCS = (qParticleTickCS*)qAssetMgr::GetInst()->FindAsset<qComputeShader>(L"ParticleTickCS").Get();

	// ��ƼŬ 100�� �ʱ� ����
	tParticle arrParticle[100] = {};
	Vec2 vResolution = qDevice::GetInst()->GetResolution();
	Vec3 vStart = Vec3(-vResolution.x / 2.f, 0.f, 100.f);	// ���� ������ ȭ�� �� ��������
	float step = vResolution.x / (float)m_MaxParticleCount;	// step(��ƼŬ�� ������ִ� �Ÿ�)�� ��ü �ػ󵵿��� ��ƼŬ ������ŭ ����

	for (int i = 0; i < m_MaxParticleCount; ++i)
	{
		arrParticle[i].Active = true;
		arrParticle[i].Mass = 1.f;
		arrParticle[i].vLocalPos = Vec3(0.f, 0.f, 0.f);
		arrParticle[i].vWorldPos = vStart + Vec3(step * (float)i, 0.f, 0.f);
	}

	//tParticle Particle = {};
	//Particle.Active = true;
	//Particle.vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	m_ParticleBuffer = new qStructuredBuffer;
	m_ParticleBuffer->Create(sizeof(tParticle), m_MaxParticleCount, SB_TYPE::SRV_UAV, true, arrParticle);

}

qParticleSystem::~qParticleSystem()
{
	if (nullptr != m_ParticleBuffer)
		delete m_ParticleBuffer;
}

void qParticleSystem::FinalTick()
{
	m_TickCS->SetParticleBuffer(m_ParticleBuffer);
	m_TickCS->Execute();
}

void qParticleSystem::Render()
{
	// ��ġ���� ���ε�
	Transform()->Binding();

	// ��ƼŬ ���� ���ε�
	m_ParticleBuffer->Binding(20);

	// ���� ���� ���ε�
	GetMaterial()->Binding();

	// ������
	GetMesh()->Render_Particle(m_MaxParticleCount);

}

void qParticleSystem::SaveToFile(FILE* _File)
{
}

void qParticleSystem::LoadFromFile(FILE* _File)
{
}
