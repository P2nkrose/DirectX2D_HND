#include "pch.h"
#include "qLevelMgr.h"

#include "qLevel.h"
#include "qLayer.h"
#include "qGameObject.h"
#include "components.h"

#include "qAssetMgr.h"
#include "assets.h"

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
	m_CurLevel = new qLevel;

	// 카메라 오브젝트
	qGameObject* CamObj = new qGameObject;
	CamObj->SetName(L"MainCamera");
	CamObj->AddComponent(new qTransform);
	CamObj->AddComponent(new qCamera);

	// 우선순위를 0 : Main Camera로 설정
	CamObj->Camera()->SetPriority(0);

	// 카메라 레이어 설정 (31번 레이어 제외 모든 레이어를 촬영)
	// 31번 UI임
	CamObj->Camera()->SetLayerAll();
	CamObj->Camera()->SetLayer(31, false);


	m_CurLevel->AddObject(0, CamObj);


	// 플레이어 오브젝트
	qGameObject* pObject = nullptr;
	pObject = new qGameObject;
	pObject->SetName(L"Player");
	pObject->AddComponent(new qTransform);
	pObject->AddComponent(new qMeshRender);

	pObject->Transform()->SetRelativePos(-0.5f, 0.5f, 0.f);
	pObject->Transform()->SetRelativeScale(0.2f, 0.2f, 0.2f);
	pObject->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pObject->MeshRender()->SetShader(qAssetMgr::GetInst()->FindAsset<qGraphicShader>(L"TestShader"));

	m_CurLevel->AddObject(0, pObject);


	m_CurLevel->Begin();
}

void qLevelMgr::Progress()
{
	m_CurLevel->Tick();
	m_CurLevel->FinalTick();
}
