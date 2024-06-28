#include "pch.h"
#include "qRenderMgr.h"

#include "qDevice.h"
#include "qConstBuffer.h"

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
	// 디버그 렌더링용 게임 오브젝트
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

	// Level 이 Play 상태인 경우, Level 내에 있는 카메라 시점으로 렌더링하기
	if (PLAY == pCurLevel->GetState())
	{
		for (size_t i = 0; i < m_vecCam.size(); ++i)
		{
			if (nullptr == m_vecCam[i])
				continue;

			m_vecCam[i]->Render();
		}
	}

	// Level 이 Stop 이나 Pause 인 경우, Editor 용 카메라 시점으로 렌더링 하기
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
	// 카메라 우선 순위에 따라서 벡터의 공간이 마련되어야 한다.
	if (m_vecCam.size() <= _CamPriority + 1)
		m_vecCam.resize(_CamPriority + 1);

	// 카메라 우선 순위에 맞는 위치에 넣는다.
	m_vecCam[_CamPriority] = _Cam;
}


void qRenderMgr::RenderStart()
{
	// 렌더타겟 지정
	Ptr<qTexture> pRTTex = qAssetMgr::GetInst()->FindAsset<qTexture>(L"RenderTargetTex");
	Ptr<qTexture> pDSTex = qAssetMgr::GetInst()->FindAsset<qTexture>(L"DepthStencilTex");
	CONTEXT->OMSetRenderTargets(1, pRTTex->GetRTV().GetAddressOf(), pDSTex->GetDSV().Get());


	// Target Clear
	float color[4] = { 0.4f, 0.4f, 0.4f, 1.f };
	CONTEXT->ClearRenderTargetView(pRTTex->GetRTV().Get(), color);
	CONTEXT->ClearDepthStencilView(pDSTex->GetDSV().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);

	g_GlobalData.g_Resolution = Vec2((float)pRTTex->Width(), (float)pRTTex->Height());
	g_GlobalData.g_Light2DCount = (int)m_vecLight2D.size();


	// Light2D 정보 업데이트 및 바인딩
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



	// GlobalData 바인딩
	static qConstBuffer* pGlobalCB = qDevice::GetInst()->GetConstBuffer(CB_TYPE::GLOBAL);
	pGlobalCB->SetData(&g_GlobalData);
	pGlobalCB->Binding();
	
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
		// 디버그 요청 모양에 맞는 메시를 가져옴
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

		// 위치 세팅
		m_DebugObject->Transform()->SetWorldMatrix((*iter).matWorld);

		// 재질 세팅
		m_DebugObject->MeshRender()->GetMaterial()->SetScalarParam(VEC4_0, (*iter).vColor);

		// 깊이판정 여부에 따라서, 쉐이더의 깊이판정 방식을 결정한다.
		if ((*iter).DepthTest)
			m_DebugObject->MeshRender()->GetMaterial()->GetShader()->SetDSType(DS_TYPE::LESS);
		else
			m_DebugObject->MeshRender()->GetMaterial()->GetShader()->SetDSType(DS_TYPE::NO_TEST_NO_WRITE);

		// 렌더링
		m_DebugObject->MeshRender()->Render();


		// 수명이 다한 디버그 정보를 삭제
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

