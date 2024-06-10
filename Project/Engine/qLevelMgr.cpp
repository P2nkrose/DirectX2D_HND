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

#include "qCollisionMgr.h"

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
	
	// Level ����
	m_CurLevel = new qLevel;

	m_CurLevel->GetLayer(0)->SetName(L"Default");
	m_CurLevel->GetLayer(1)->SetName(L"Background");
	m_CurLevel->GetLayer(2)->SetName(L"Tile");
	m_CurLevel->GetLayer(3)->SetName(L"Player");
	m_CurLevel->GetLayer(4)->SetName(L"Monster");


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
	CamObj->Camera()->SetFar(100000.f);
	CamObj->Camera()->SetProjType(ORTHOGRAPHIC);
	//CamObj->Camera()->SetProjType(PERSPECTIVE);

	m_CurLevel->AddObject(0, CamObj);


	// ------------------------------------------------


	qGameObject* pObject = nullptr;

	// �÷��̾� ������Ʈ
	pObject = new qGameObject;
	pObject->SetName(L"Player");
	pObject->AddComponent(new qTransform);
	pObject->AddComponent(new qMeshRender);
	pObject->AddComponent(new qCollider2D);
	pObject->AddComponent(new qPlayerScript);

	pObject->Transform()->SetRelativePos(0.f, 0.0f, 100.f);
	pObject->Transform()->SetRelativeScale(200.f, 200.f, 1.f);

	pObject->Collider2D()->SetIndependentScale(true);
	pObject->Collider2D()->SetOffset(Vec3(20.f, 0.f, 0.f));
	pObject->Collider2D()->SetScale(Vec3(220.f, 220.f, 1.f));
	
	pObject->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pObject->MeshRender()->SetMaterial(pMtrl);
	pObject->MeshRender()->GetMaterial()->SetScalarParam(INT_1, 1);
	pObject->MeshRender()->GetMaterial()->SetScalarParam(FLOAT_0, 0.01f);
	pObject->MeshRender()->GetMaterial()->SetScalarParam(VEC4_0, Vec4(0.f, 1.f, 0.f, 1.f));

	
	// Child ������Ʈ
	qGameObject* pChild = new qGameObject;
	pChild->SetName(L"Child");

	pChild->AddComponent(new qTransform);
	pChild->AddComponent(new qMeshRender);
	pChild->AddComponent(new qCollider2D);

	pChild->Transform()->SetRelativePos(400.f, 0.f, 0.f);
	pChild->Transform()->SetRelativeScale(100.f, 100.f, 1.f);
	pChild->Transform()->SetIndependentScale(true);

	pChild->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pChild->Collider2D()->SetScale(Vec3(1.2f, 1.2f, 1.f));

	pChild->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pChild->MeshRender()->SetMaterial(pMtrl);

	pObject->AddChild(pChild);

	m_CurLevel->AddObject(3, pObject);




	// Monster Object
	qGameObject* pMonster = new qGameObject;
	pMonster->SetName(L"Monster");

	pMonster->AddComponent(new qTransform);
	pMonster->AddComponent(new qMeshRender);
	pMonster->AddComponent(new qCollider2D);

	pMonster->Transform()->SetRelativePos(-400.f, 0.f, 100.f);
	pMonster->Transform()->SetRelativeScale(150.f, 150.f, 1.f);

	pMonster->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pMonster->Collider2D()->SetScale(Vec3(1.2f, 1.2f, 1.f));

	pMonster->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pMonster->MeshRender()->SetMaterial(pMtrl);

	m_CurLevel->AddObject(4, pMonster);

	// �浹 ����
	qCollisionMgr::GetInst()->CollisionCheck(3, 4);




	
	// ���� ����
	m_CurLevel->Begin();
}

void qLevelMgr::Progress()
{
	m_CurLevel->Tick();
	m_CurLevel->ClearObject();
	m_CurLevel->FinalTick();
}
