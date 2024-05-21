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
	, m_ProjType(PROJ_TYPE::ORTHOGRAPHIC)
	, m_Width(0)
	, m_Height(0)
	, m_Far(500.f)
	, m_FOV(XM_PI / 2.f)
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
	// ī�޶� ���
	if (-1 != m_Priority)
	{
		qRenderMgr::GetInst()->RegisterCamera(this, m_Priority);
	}
}

void qCamera::FinalTick()
{
	// View Space �� ī�޶� ��ǥ���� ������ �Ǵ� ��ǥ��
	// 1. ī�޶� ������ ����
	// 2. ī�޶� �ٶ󺸴� ������ Z��

	// View ����� ����Ѵ�.
	// View ����� World Space -> View Space �� �����Ҷ� ����ϴ� ���

	m_matView = XMMatrixTranslation(-Transform()->GetRelativePos().x
								  , -Transform()->GetRelativePos().y
								  , -Transform()->GetRelativePos().z);

	// Projection Space ���� ��ǥ�� (NDC)
	if (PROJ_TYPE::ORTHOGRAPHIC == m_ProjType)
	{
		// 1. ���� ���� (Orthographic)
		// ������ ����������
		// �þ� ������ NDC �� ����
		m_matProj = XMMatrixOrthographicLH(m_Width, m_Height, 1.f, 10000.f);
	}
	else
	{
		// 2. ���� ���� (Perspective)
		float AspectRatio = m_Width / m_Height;
		m_matProj = XMMatrixPerspectiveFovLH(m_FOV, AspectRatio, 1.f, m_Far);
	}
	

	


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
