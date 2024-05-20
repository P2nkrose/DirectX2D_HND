#include "pch.h"
#include "qCamera.h"

#include "qRenderMgr.h"

#include "qLevelMgr.h"
#include "qLevel.h"
#include "qLayer.h"
#include "qGameObject.h"


qCamera::qCamera()
	: qComponent(COMPONENT_TYPE::CAMERA)
	, m_Priority(-1)
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
	// View Space 란 카메라가 좌표계의 기준이 되는 좌표계
	// 1. 카메라가 원점에 존재
	// 2. 카메라가 바라보는 방향이 Z축

	// View 행렬을 계산한다.
	// View 행렬은 World Space -> View Space 로 변경할때 사용하는 행렬



}

void qCamera::Render()
{
	g_Trans.matView = m_matView;

	qLevel* pLevel = qLevelMgr::GetInst()->GetCurrentLevel();

	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		qLayer* pLayer = pLevel->GetLayer(i);
		const vector<qGameObject*>& vecObjects = pLayer->GetParentObjects();
		for (size_t j = 0; j < vecObjects.size(); ++j)
		{
			vecObjects[j]->Render();
		}
	}
}
