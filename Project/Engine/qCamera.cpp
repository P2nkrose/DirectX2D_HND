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
	, m_Far(10000.f)
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

	// 1. ī�޶� �ִ� ���� �����̾��� ��츦 �������� �� ��ü���� ��ǥ�� �˾Ƴ��� �Ѵ�.
	// 2. ī�޶� ���忡�� �ٶ󺸴� ������ Z ������ �����ξ�� �Ѵ�.
	//	  ��ü�鵵 ���� ȸ���� �Ѵ�.

	// View ����� ����Ѵ�.
	// View ����� World Space -> View Space �� �����Ҷ� ����ϴ� ���

	// �̵� ���
	Matrix matTrans = XMMatrixTranslation(-Transform()->GetRelativePos().x
										, -Transform()->GetRelativePos().y
										, -Transform()->GetRelativePos().z);

	// ȸ�� ���
	Matrix matRot;
	Vec3 vR = Transform()->GetDir(DIR::RIGHT);
	Vec3 vU = Transform()->GetDir(DIR::UP);
	Vec3 vF = Transform()->GetDir(DIR::FRONT);

	matRot._11 = vR.x; matRot._12 = vU.x; matRot._13 = vF.x;
	matRot._21 = vR.y; matRot._22 = vU.y; matRot._23 = vF.y;
	matRot._31 = vR.z; matRot._32 = vU.z; matRot._33 = vF.z;

	m_matView = matTrans * matRot;


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
