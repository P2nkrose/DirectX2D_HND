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
	m_CurLevel = new qLevel;

	// ī�޶� ������Ʈ
	qGameObject* CamObj = new qGameObject;
	CamObj->SetName(L"MainCamera");
	CamObj->AddComponent(new qTransform);
	CamObj->AddComponent(new qCamera);
	CamObj->AddComponent(new qCameraMoveScript);

	// �켱������ 0 : Main Camera�� ����
	CamObj->Camera()->SetPriority(0);

	// ī�޶� ���̾� ���� (31�� ���̾� ���� ��� ���̾ �Կ�)
	// 31�� UI��
	CamObj->Camera()->SetLayerAll();
	CamObj->Camera()->SetLayer(31, false);
	CamObj->Camera()->SetFar(10000.f);
	//CamObj->Camera()->SetProjType(ORTHOGRAPHIC);
	CamObj->Camera()->SetProjType(PERSPECTIVE);


	m_CurLevel->AddObject(0, CamObj);


	// �÷��̾� ������Ʈ
	qGameObject* pObject = nullptr;
	pObject = new qGameObject;
	pObject->SetName(L"Player");
	pObject->AddComponent(new qTransform);
	pObject->AddComponent(new qMeshRender);
	pObject->AddComponent(new qPlayerScript);

	pObject->Transform()->SetRelativePos(0.f, 0.0f, 100.f);
	pObject->Transform()->SetRelativeScale(200.f, 200.f, 1.f);
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
