#include "pch.h"
#include "qLevelMgr.h"

#include "qLevel.h"
#include "qLayer.h"
#include "qGameObject.h"
#include "components.h"

#include "qAssetMgr.h"
#include "assets.h"

#include "qPlayerScript.h"
#include "qCameraMoveScript.h"

qLevelMgr::qLevelMgr()
	: m_CurLevel(nullptr)
{

}


qLevelMgr::~qLevelMgr()
{
	if (nullptr != m_CurLevel)
		delete m_CurLevel;
}

void qLevelMgr::Init()
{
	// Material
	Ptr<qMaterial> pMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DMtrl");
	Ptr<qMaterial> pAlphaBlendMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DAlphaBlendMtrl");
	Ptr<qMaterial> pDebugShapeMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"DebugShapeMtrl");

	Ptr<qTexture> pTexture = qAssetMgr::GetInst()->Load<qTexture>(L"PlayerTex", L"texture\\Character.png");


	pAlphaBlendMtrl->SetTexParam(TEX_0, pTexture);
	

	m_CurLevel = new qLevel;

	// 카메라 오브젝트
	qGameObject* CamObj = new qGameObject;
	CamObj->SetName(L"MainCamera");
	CamObj->AddComponent(new qTransform);
	CamObj->AddComponent(new qCamera);
	CamObj->AddComponent(new qCameraMoveScript);

	// 우선순위를 0 : Main Camera로 설정
	CamObj->Camera()->SetPriority(0);

	// 카메라 레이어 설정 (31번 레이어 제외 모든 레이어를 촬영)
	// 31번 UI임
	CamObj->Camera()->SetLayerAll();
	CamObj->Camera()->SetLayer(31, false);
	CamObj->Camera()->SetFar(10000.f);
	CamObj->Camera()->SetProjType(ORTHOGRAPHIC);
	//CamObj->Camera()->SetProjType(PERSPECTIVE);

	m_CurLevel->AddObject(0, CamObj);


	// ------------------------------------------------


	qGameObject* pObject = nullptr;

	// 플레이어 오브젝트
	pObject = new qGameObject;
	pObject->SetName(L"Player");
	pObject->AddComponent(new qTransform);
	pObject->AddComponent(new qMeshRender);
	pObject->AddComponent(new qPlayerScript);

	pObject->Transform()->SetRelativePos(0.f, 0.0f, 100.f);
	pObject->Transform()->SetRelativeScale(200.f, 200.f, 1.f);
	
	pObject->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pObject->MeshRender()->SetMaterial(pDebugShapeMtrl);
	pObject->MeshRender()->GetMaterial()->SetScalarParam(INT_1, 1);
	pObject->MeshRender()->GetMaterial()->SetScalarParam(FLOAT_0, 0.01f);
	pObject->MeshRender()->GetMaterial()->SetScalarParam(VEC4_0, Vec4(0.f, 1.f, 0.f, 1.f));

	m_CurLevel->AddObject(0, pObject);




	// 몬스터 오브젝트
	pObject = new qGameObject;
	pObject->SetName(L"Monster");
	pObject->AddComponent(new qTransform);
	pObject->AddComponent(new qMeshRender);


	pObject->Transform()->SetRelativePos(100.f, 0.0f, 200.f);
	pObject->Transform()->SetRelativeScale(200.f, 200.f, 1.f);

	pObject->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pObject->MeshRender()->SetMaterial(pMtrl);

	m_CurLevel->AddObject(0, pObject);


	m_CurLevel->Begin();
}

void qLevelMgr::Progress()
{
	m_CurLevel->Tick();
	m_CurLevel->FinalTick();
}
