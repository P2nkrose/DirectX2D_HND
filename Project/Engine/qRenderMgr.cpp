#include "pch.h"
#include "qRenderMgr.h"

#include "qDevice.h"

#include "qCamera.h"
#include "qTimeMgr.h"
#include "qAssetMgr.h"

#include "qGameObject.h"
#include "qTransform.h"
#include "qMeshRender.h"

#include "qLevelMgr.h"
#include "qLevel.h"

#include "qLight2D.h"
#include "qStructuredBuffer.h"


qRenderMgr::qRenderMgr()
	: m_EditorCamera(nullptr)
	, m_Light2DBuffer(nullptr)
{
	m_Light2DBuffer = new qStructuredBuffer;
}

qRenderMgr::~qRenderMgr()
{
	if (nullptr != m_DebugObject)
		delete m_DebugObject;

	if (nullptr != m_Light2DBuffer)
		delete m_Light2DBuffer;
}


void qRenderMgr::Init()
{
	// ����� �������� ���� ������Ʈ
	m_DebugObject = new qGameObject;
	m_DebugObject->AddComponent(new qTransform);
	m_DebugObject->AddComponent(new qMeshRender);
	m_DebugObject->MeshRender()->SetMaterial(qAssetMgr::GetInst()->FindAsset<qMaterial>(L"DebugShapeMtrl"));
}

void qRenderMgr::Tick()
{
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	if (nullptr == pCurLevel)
		return;

	RenderStart();

	// Level �� Play ������ ���, Level ���� �ִ� ī�޶� �������� �������ϱ�
	if (PLAY == pCurLevel->GetState())
	{
		for (size_t i = 0; i < m_vecCam.size(); ++i)
		{
			if (nullptr == m_vecCam[i])
				continue;

			m_vecCam[i]->Render();
		}
	}

	// Level �� Stop �̳� Pause �� ���, Editor �� ī�޶� �������� ������ �ϱ�
	else
	{
		if (nullptr != m_EditorCamera)
		{
			m_EditorCamera->Render();
		}
	}

	// Debug Render
	RenderDebugShape();

	// Clear
	Clear();
}

void qRenderMgr::RegisterCamera(qCamera* _Cam, int _CamPriority)
{
	// ī�޶� �켱 ������ ���� ������ ������ ���õǾ�� �Ѵ�.
	if (m_vecCam.size() <= _CamPriority + 1)
		m_vecCam.resize(_CamPriority + 1);

	// ī�޶� �켱 ������ �´� ��ġ�� �ִ´�.
	m_vecCam[_CamPriority] = _Cam;
}


void qRenderMgr::RenderStart()
{
	// ����Ÿ�� ����
	Ptr<qTexture> pRTTex = qAssetMgr::GetInst()->FindAsset<qTexture>(L"RenderTargetTex");
	Ptr<qTexture> pDSTex = qAssetMgr::GetInst()->FindAsset<qTexture>(L"DepthStencilTex");
	CONTEXT->OMSetRenderTargets(1, pRTTex->GetRTV().GetAddressOf(), pDSTex->GetDSV().Get());


	// Light2D ���� ������Ʈ �� ���ε�
	vector<tLightInfo> vecLight2DInfo;
	for (size_t i = 0; i < m_vecLight2D.size(); ++i)
	{
		vecLight2DInfo.push_back(m_vecLight2D[i]->GetLightInfo());
	}

	if (m_Light2DBuffer->GetElementCount() < vecLight2DInfo.size())
	{
		m_Light2DBuffer->Create(sizeof(tLightInfo), vecLight2DInfo.size());
	}

	m_Light2DBuffer->SetData(vecLight2DInfo.data());
	m_Light2DBuffer->Binding(11);
	
}

void qRenderMgr::Clear()
{
	m_vecLight2D.clear();
}

void qRenderMgr::RenderDebugShape()
{
	list<tDebugShapeInfo>::iterator iter = m_DebugShapeList.begin();

	for (; iter != m_DebugShapeList.end(); )
	{
		// ����� ��û ��翡 �´� �޽ø� ������
		switch ((*iter).Shape)
		{
		case DEBUG_SHAPE::RECT:
			m_DebugObject->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh_Debug"));
			break;
		case DEBUG_SHAPE::CIRCLE:
			m_DebugObject->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"CircleMesh_Debug"));
			break;
		case DEBUG_SHAPE::LINE:

			break;
		case DEBUG_SHAPE::CUBE:

			break;
		case DEBUG_SHAPE::SPHERE:

			break;
		}

		// ��ġ ����
		m_DebugObject->Transform()->SetWorldMatrix((*iter).matWorld);

		// ���� ����
		m_DebugObject->MeshRender()->GetMaterial()->SetScalarParam(VEC4_0, (*iter).vColor);

		// �������� ���ο� ����, ���̴��� �������� ����� �����Ѵ�.
		if ((*iter).DepthTest)
			m_DebugObject->MeshRender()->GetMaterial()->GetShader()->SetDSType(DS_TYPE::LESS);
		else
			m_DebugObject->MeshRender()->GetMaterial()->GetShader()->SetDSType(DS_TYPE::NO_TEST_NO_WRITE);

		// ������
		m_DebugObject->MeshRender()->Render();


		// ������ ���� ����� ������ ����
		(*iter).Age += EngineDT;
		if ((*iter).LifeTime < (*iter).Age)
		{
			iter = m_DebugShapeList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

