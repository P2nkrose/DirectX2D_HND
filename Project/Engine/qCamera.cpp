#include "pch.h"
#include "qCamera.h"

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
{
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
	Vec3 vWorldPos = Transform()->GetRelativePos();

	if (KEY_PRESSED(KEY::A))
		vWorldPos.x -= DT * 1.f;
	if (KEY_PRESSED(KEY::D))
		vWorldPos.x += DT * 1.f;

	Transform()->SetRelativePos(vWorldPos);

	// View Space 란 카메라가 좌표계의 기준이 되는 좌표계
	// 1. 카메라가 원점에 존재
	// 2. 카메라가 바라보는 방향이 Z축

	// View 행렬을 계산한다.
	// View 행렬은 World Space -> View Space 로 변경할때 사용하는 행렬

	m_matView = XMMatrixTranslation(-vWorldPos.x, -vWorldPos.y, -vWorldPos.z);

	// Projection Space 투명 좌표계 (NDC)

}

void qCamera::Render()
{
	g_Trans.matView = m_matView;

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
