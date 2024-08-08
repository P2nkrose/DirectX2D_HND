#include "pch.h"
#include "qParticleSystem.h"

#include "qTimeMgr.h"

#include "qDevice.h"
#include "qAssetMgr.h"
#include "qStructuredBuffer.h"

#include "qTransform.h"


qParticleSystem::qParticleSystem()
	: qRenderComponent(COMPONENT_TYPE::PARTICLESYSTEM)
	, m_ParticleBuffer(nullptr)
	, m_SpawnCountBuffer(nullptr)
	, m_Time(0.f)
	, m_MaxParticleCount(100)
{
	// Mesh / Material
	SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"PointMesh"));
	SetMaterial(qAssetMgr::GetInst()->FindAsset<qMaterial>(L"ParticleRenderMtrl"));

	// ParticleTick ComputeShader
	m_TickCS = (qParticleTickCS*)qAssetMgr::GetInst()->FindAsset<qComputeShader>(L"ParticleTickCS").Get();

	m_ParticleTex = qAssetMgr::GetInst()->FindAsset<qTexture>(L"texture\\particle\\CartoonSmoke.png");

	// 파티클 100개 초기 설정
	tParticle arrParticle[100] = {};

	float Angle = XM_2PI / m_MaxParticleCount;
	//Vec2 vResolution = qDevice::GetInst()->GetResolution();
	//Vec3 vStart = Vec3(-vResolution.x / 2.f, 0.f, 100.f);	// 시작 지점을 화면 맨 왼쪽으로
	//float step = vResolution.x / (float)m_MaxParticleCount;	// step(파티클이 띄워져있는 거리)를 전체 해상도에서 파티클 갯수만큼 나눔
	


	for (int i = 0; i < m_MaxParticleCount; ++i)
	{
		arrParticle[i].Active = false;
		arrParticle[i].Mass = 1.f;
		arrParticle[i].vLocalPos = Vec3(0.f, 0.f, 0.f);
		arrParticle[i].vWorldPos = Vec3(0.f, 0.f, 0.f);
		arrParticle[i].vWorldScale = Vec3(20.f, 20.f, 0.f);
		arrParticle[i].vColor = Vec4(0.9, 0.34f, 0.5, 1.f);

		arrParticle[i].vVelocity = Vec3(cosf(Angle * (float)i), sinf(Angle * (float)i), 0.f) * 200.f;

	}

	//tParticle Particle = {};
	//Particle.Active = true;
	//Particle.vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	m_ParticleBuffer = new qStructuredBuffer;
	m_ParticleBuffer->Create(sizeof(tParticle), m_MaxParticleCount, SB_TYPE::SRV_UAV, true, arrParticle);

	m_SpawnCountBuffer = new qStructuredBuffer;
	m_SpawnCountBuffer->Create(sizeof(tSpawnCount), 1, SB_TYPE::SRV_UAV, true, nullptr);
}

qParticleSystem::~qParticleSystem()
{
	DELETE(m_ParticleBuffer);
	DELETE(m_SpawnCountBuffer);

}

void qParticleSystem::FinalTick()
{
	// SpawnCount
	m_Time += EngineDT;

	tSpawnCount count = {};

	if (1.f <= m_Time)
	{
		count.iSpawnCount = 5;
		m_Time = 0.f;
	}

	m_SpawnCountBuffer->SetData(&count);

	m_TickCS->SetParticleBuffer(m_ParticleBuffer);
	m_TickCS->SetSpawnCount(m_SpawnCountBuffer);
	m_TickCS->Execute();
}

void qParticleSystem::Render()
{
	// 위치정보 바인딩
	Transform()->Binding();

	// 파티클 버퍼 바인딩
	m_ParticleBuffer->Binding(20);	// t20

	// 재질 정보 바인딩
	GetMaterial()->SetTexParam(TEX_0, m_ParticleTex);
	GetMaterial()->Binding();

	// 랜더링
	GetMesh()->Render_Particle(m_MaxParticleCount);

	// 파티클 버퍼 바인딩 해제
	m_ParticleBuffer->Clear(20);

}

void qParticleSystem::SaveToFile(FILE* _File)
{
}

void qParticleSystem::LoadFromFile(FILE* _File)
{
}
