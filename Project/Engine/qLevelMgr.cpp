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


	pObject = new qGameObject;
	pObject->SetName(L"Monster");
	pObject->AddComponent(new qTransform);
	pObject->AddComponent(new qMeshRender);

	pObject->Transform()->SetRelativePos(0.5f, 0.f, 0.f);
	pObject->Transform()->SetRelativeScale(0.5f, 0.5f, 0.5f);
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

void qLevelMgr::Render()
{
	m_CurLevel->Render();
}
