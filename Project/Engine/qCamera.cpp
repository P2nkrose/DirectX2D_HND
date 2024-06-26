#include "pch.h"
#include "qCamera.h"

#include "qDevice.h"

#include "qRenderMgr.h"

#include "qLevelMgr.h"
#include "qLevel.h"
#include "qLayer.h"
#include "qGameObject.h"
#include "qRenderComponent.h"

#include "qTimeMgr.h"
#include "qKeyMgr.h"
#include "qTransform.h"


qCamera::qCamera()
	: qComponent(COMPONENT_TYPE::CAMERA)
	, m_Priority(-1)
	, m_LayerCheck(0)
	, m_ProjType(PROJ_TYPE::ORTHOGRAPHIC)
	, m_Width(0)
	, m_Height(0)
	, m_Far(100000.f)
	, m_FOV(XM_PI / 2.f)
	, m_ProjectionScale(1.f)
{
	Vec2 vResolution = qDevice::GetInst()->GetResolution();
	m_Width = vResolution.x;
	m_Height = vResolution.y;
	m_AspectRatio = m_Width / m_Height;
}

qCamera::~qCamera()
{
}

void qCamera::Begin()
{
	// 카메라를 등록
	if (-1 != m_Priority)
	{
		qRenderMgr::GetInst()->RegisterCamera(this, m_Priority);
	}
}

void qCamera::FinalTick()
{
	// View Space 란 카메라가 좌표계의 기준이 되는 좌표계
	// 1. 카메라가 원점에 존재
	// 2. 카메라가 바라보는 방향이 Z축

	// 1. 카메라가 있는 곳이 원점이었을 경우를 기준으로 한 물체들의 좌표를 알아내야 한다.
	// 2. 카메라가 월드에서 바라보던 방향을 Z 축으로 돌려두어야 한다.
	//	  물체들도 같이 회전을 한다.

	// View 행렬을 계산한다.
	// View 행렬은 World Space -> View Space 로 변경할때 사용하는 행렬

	// 이동 행렬
	Matrix matTrans = XMMatrixTranslation(-Transform()->GetRelativePos().x
										, -Transform()->GetRelativePos().y
										, -Transform()->GetRelativePos().z);

	// 회전 행렬
	Matrix matRot;
	Vec3 vR = Transform()->GetWorldDir(DIR::RIGHT);
	Vec3 vU = Transform()->GetWorldDir(DIR::UP);
	Vec3 vF = Transform()->GetWorldDir(DIR::FRONT);

	matRot._11 = vR.x; matRot._12 = vU.x; matRot._13 = vF.x;
	matRot._21 = vR.y; matRot._22 = vU.y; matRot._23 = vF.y;
	matRot._31 = vR.z; matRot._32 = vU.z; matRot._33 = vF.z;

	m_matView = matTrans * matRot;


	// Projection Space 투영 좌표계 (NDC)
	if (PROJ_TYPE::ORTHOGRAPHIC == m_ProjType)
	{
		// 1. 직교 투영 (Orthographic)
		// 투영을 일직선으로
		// 시야 범위를 NDC 로 압축
		m_matProj = XMMatrixOrthographicLH(m_Width * m_ProjectionScale, m_Height * m_ProjectionScale, 1.f, 10000.f);
	}
	else
	{
		// 2. 원근 투영 (Perspective)
		m_matProj = XMMatrixPerspectiveFovLH(m_FOV, m_AspectRatio, 1.f, m_Far);
	}
}

// 렌더링 분류하기
void qCamera::SortGameObject()
{
	qLevel* pLevel = qLevelMgr::GetInst()->GetCurrentLevel();

	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		if (false == (m_LayerCheck & (1 << i)))
			continue;

		qLayer* pLayer = pLevel->GetLayer(i);

		const vector<qGameObject*>& vecObjects = pLayer->GetObjects();
		for (size_t j = 0; j < vecObjects.size(); ++j)
		{
			if (nullptr == vecObjects[j]->GetRenderComponent()
				|| nullptr == vecObjects[j]->GetRenderComponent()->GetMesh()
				|| nullptr == vecObjects[j]->GetRenderComponent()->GetMaterial()
				|| nullptr == vecObjects[j]->GetRenderComponent()->GetMaterial()->GetShader())
			{
				continue;
			}

			Ptr<qGraphicShader> pShader = vecObjects[j]->GetRenderComponent()->GetMaterial()->GetShader();
			SHADER_DOMAIN Domain = pShader->GetDomain();

			switch (Domain)
			{
			case DOMAIN_OPAQUE:
				m_vecOpaque.push_back(vecObjects[j]);
				break;
			case DOMAIN_MASKED:
				m_vecMasked.push_back(vecObjects[j]);
				break;
			case DOMAIN_TRANSPARENT:
				m_vecTransparent.push_back(vecObjects[j]);
				break;
			case DOMAIN_PARTICLE:
				m_vecParticles.push_back(vecObjects[j]);
				break;
			}
		}
	}
}


void qCamera::Render()
{
	// 오브젝트 분류
	SortGameObject();


	// 물체가 렌더링 될때 사용할 View, Proj 행렬
	g_Trans.matView = m_matView;
	g_Trans.matProj = m_matProj;

	// Opaque
	for (size_t i = 0; i < m_vecOpaque.size(); ++i)
	{
		m_vecOpaque[i]->Render();
	}

	// Masked
	for (size_t i = 0; i < m_vecMasked.size(); ++i)
	{
		m_vecMasked[i]->Render();
	}

	// Transparent
	for (size_t i = 0; i < m_vecTransparent.size(); ++i)
	{
		m_vecTransparent[i]->Render();
	}

	// Particles
	for (size_t i = 0; i < m_vecParticles.size(); ++i)
	{
		m_vecParticles[i]->Render();
	}

	m_vecOpaque.clear();
	m_vecMasked.clear();
	m_vecTransparent.clear();
	m_vecParticles.clear();
}

