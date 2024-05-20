#include "pch.h"
#include "qCamera.h"

#include "qDevice.h"

#include "qRenderMgr.h"

#include "qLevelMgr.h"
#include "qLevel.h"
#include "qLayer.h"
#include "qGameObject.h"

#include "qTimeMgr.h"
#include "qKeyMgr.h"
#include "qTransform.h"


qCamera::qCamera()
	: qComponent(COMPONENT_TYPE::CAMERA)
	, m_Priority(-1)
	, m_LayerCheck(0)
	, m_Width(0)
	, m_Height(0)
{
	Vec2 vResolution = qDevice::GetInst()->GetResolution();
	m_Width = vResolution.x;
	m_Height = vResolution.y;
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
	// 카메라 이동 Script 에서 동작하게 구현!
	// =======================================

	//Vec3 vWorldPos = Transform()->GetRelativePos();

	//if (KEY_PRESSED(KEY::A))
	//	vWorldPos.x -= DT * 1.f;
	//if (KEY_PRESSED(KEY::D))
	//	vWorldPos.x += DT * 1.f;

	//Transform()->SetRelativePos(vWorldPos);

	// =======================================



	// View Space 란 카메라가 좌표계의 기준이 되는 좌표계
	// 1. 카메라가 원점에 존재
	// 2. 카메라가 바라보는 방향이 Z축

	// View 행렬을 계산한다.
	// View 행렬은 World Space -> View Space 로 변경할때 사용하는 행렬

	m_matView = XMMatrixTranslation(-Transform()->GetRelativePos().x
								  , -Transform()->GetRelativePos().y
								  , -Transform()->GetRelativePos().z);

	// Projection Space 투영 좌표계 (NDC)
	// 1. 직교 투영 (Orthographic)
	// 투영을 일직선으로
	// 시야 범위를 NDC 로 압축
	m_matProj = XMMatrixOrthographicLH(m_Width, m_Height, 1.f, 10000.f);

	// 2. 원근 투영 (Perspective)


}

void qCamera::Render()
{
	g_Trans.matView = m_matView;
	g_Trans.matProj = m_matProj;

	qLevel* pLevel = qLevelMgr::GetInst()->GetCurrentLevel();

	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		if (false == (m_LayerCheck & (1 << i)))
			continue;

		qLayer* pLayer = pLevel->GetLayer(i);
		const vector<qGameObject*>& vecObjects = pLayer->GetParentObjects();
		for (size_t j = 0; j < vecObjects.size(); ++j)
		{
			vecObjects[j]->Render();
		}
	}
}
