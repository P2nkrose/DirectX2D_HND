#include "pch.h"
#include "qLevel_stage1.h"

#include <Engine/qAssetMgr.h>
#include <Engine/assets.h>

#include <Engine/qFSM.h>
#include <Engine/qState.h>

#include <Engine/qCollisionMgr.h>
#include <Engine/qCollider2D.h>
#include <Engine/qLevelMgr.h>

#include <Engine/qLevel.h>
#include <Engine/qLayer.h>
#include <Engine/qGameObject.h>
#include <Engine/components.h>

#include <Scripts/qPlayerScript.h>
#include <Scripts/qMissileScript.h>
#include <Scripts/qCameraMoveScript.h>
#include <Scripts/qPlatformScript.h>

#include <Engine/qSetColorCS.h>
#include <Engine/qStructuredBuffer.h>

#include <States/qStateMgr.h>
#include <States/qPlayerIdleState.h>			// 0
#include <States/qPlayerRunState.h>				// 2
#include <States/qPlayerIdleToRunState.h>		// 3
#include <States/qPlayerRunToIdleState.h>		// 4
#include <States/qPlayerIdleUTurnState.h>		// 5
#include <States/qPlayerRunUTurnState.h>		// 6


#include "qLevelSaveLoad.h"


void qLevel_stage1::CreateStage1()
{
	// Sound


	// Material
	Ptr<qMaterial> pMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DMtrl");
	Ptr<qMaterial> pAlphaBlendMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DAlphaBlendMtrl");
	Ptr<qMaterial> pDebugShapeMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"DebugShapeMtrl");

	Ptr<qMaterial> pMtrl2 = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"material\\stage1Back.mtrl");

	//Ptr<qTexture> pBackStage1 = qAssetMgr::GetInst()->FindAsset<qTexture>(L"texture\\map\\stage1");
	//pMtrl->SetTexParam(TEX_0, pBackStage1);

	// Prefab
	CreatePrefab();


	// Level
	qLevel* pStage1 = new qLevel;
	pStage1->SetName(L"stage1");

	pStage1->GetLayer(0)->SetName(L"Camera");
	pStage1->GetLayer(1)->SetName(L"Background");
	pStage1->GetLayer(2)->SetName(L"Platform");
	pStage1->GetLayer(3)->SetName(L"Player");
	pStage1->GetLayer(4)->SetName(L"Monster");
	pStage1->GetLayer(5)->SetName(L"UI");


	// Camera
	qGameObject* CameraObject = new qGameObject;
	CameraObject->SetName(L"MainCamera");
	CameraObject->AddComponent(new qCameraMoveScript);

	CameraObject->AddComponent(new qTransform);

	CameraObject->AddComponent(new qCamera);
	// 우선순위를 0 : Main Camera 로 설정
	CameraObject->Camera()->SetPriority(0);

	// 카메라 레이어 설정
	CameraObject->Camera()->SetLayerAll();
	CameraObject->Camera()->SetFar(100000.f);
	CameraObject->Camera()->SetProjType(ORTHOGRAPHIC);		// 직교 투영

	pStage1->AddObject(0, CameraObject);


	// 배경
	qGameObject* pBackground = new qGameObject;
	pBackground->SetName(L"Background");
	
	pBackground->AddComponent(new qTransform);
	pBackground->Transform()->SetRelativePos(0.f, 0.f, 50.f);
	pBackground->Transform()->SetRelativeScale(2048.f, 1789.f, 1.f);

	pBackground->AddComponent(new qMeshRender);
	pBackground->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pBackground->MeshRender()->SetMaterial(pMtrl2);

	pStage1->AddObject(1, pBackground);

	// Platform
	// Collider WorldPos로 해야됨
	qGameObject* pPlatform = new qGameObject;
	pPlatform->SetName(L"Platform");
	pPlatform->AddComponent(new qPlatformScript);

	pPlatform->AddComponent(new qTransform);
	pPlatform->Transform()->SetRelativePos(0.f, -400.f, 10.f);
	pPlatform->Transform()->SetRelativeScale(600.f, 100.f, 1.f);

	pPlatform->AddComponent(new qCollider2D);
	pPlatform->Collider2D()->SetIndependentScale(false);
	pPlatform->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	pStage1->AddObject(2, pPlatform);



	// 광원 오브젝트
	qGameObject* pLight = new qGameObject;
	pLight->SetName(L"PointLight 1");
	pLight->AddComponent(new qTransform);
	pLight->AddComponent(new qLight2D);

	pLight->Light2D()->SetLightType(LIGHT_TYPE::POINT);
	pLight->Light2D()->SetLightColor(Vec3(1.f, 1.f, 1.f));
	pLight->Light2D()->SetRadius(1000.f);

	//pStage1->AddObject(0, pLight);



	// 플레이어 오브젝트
	qGameObject* pPlayer = new qGameObject;
	pPlayer->SetName(L"Player");
	pPlayer->AddComponent(new qPlayerScript);
	pPlayer->AddChild(pLight);
	//pPlayer->AddChild(CameraObject);
	

	pPlayer->AddComponent(new qTransform);
	pPlayer->Transform()->SetRelativePos(0.f, 0.0f, 10.f);
	pPlayer->Transform()->SetRelativeScale(130.f, 130.f, 1.f);

	pPlayer->AddComponent(new qMeshRender);
	pPlayer->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pPlayer->MeshRender()->SetMaterial(pMtrl);

	pPlayer->AddComponent(new qFlipBookComponent);
	
	Ptr<qFlipBook> pDeathIdle = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\death_idle_right.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(0, pDeathIdle);

	Ptr<qFlipBook> pDeathRun = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\death_run.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(2, pDeathRun);

	Ptr<qFlipBook> pDeathIdleToRun = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\idletorun_2.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(3, pDeathIdleToRun);

	Ptr<qFlipBook> pDeathRunToIdle = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\runtoidle.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(4, pDeathRunToIdle);

	Ptr<qFlipBook> pDeathIdleUTurn = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\idleuturn_2.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(5, pDeathIdleUTurn);

	Ptr<qFlipBook> pDeathRunUTurn = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\runuturn.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(6, pDeathRunUTurn);

	pPlayer->FlipBookComponent()->Play(0, 10, true);

	pPlayer->AddComponent(new qRigidBody);
	pPlayer->RigidBody()->SetMass(1.f);
	pPlayer->RigidBody()->SetMaxWalkSpeed(300.f);
	pPlayer->RigidBody()->SetFriction(100.f);
	pPlayer->RigidBody()->UseGravity(true);
	pPlayer->RigidBody()->SetMaxGravitySpeed(1500.f);
	pPlayer->RigidBody()->SetJumpSpeed(400.f);
	pPlayer->RigidBody()->SetGround(false);

	pPlayer->AddComponent(new qCollider2D);
	pPlayer->Collider2D()->SetIndependentScale(false);
	pPlayer->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlayer->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	pPlayer->AddComponent(new qFSM);
	pPlayer->FSM()->AddState(L"Idle", new qPlayerIdleState);				// 0
	pPlayer->FSM()->AddState(L"Run", new qPlayerRunState);					// 2
	pPlayer->FSM()->AddState(L"IdleToRun", new qPlayerIdleToRunState);		// 3
	pPlayer->FSM()->AddState(L"RunToIdle", new qPlayerRunToIdleState);		// 4
	pPlayer->FSM()->AddState(L"IdleUTurn", new qPlayerIdleUTurnState);		// 5
	pPlayer->FSM()->AddState(L"RunUTurn", new qPlayerRunUTurnState);		// 6

	
	pPlayer->FSM()->ChangeState(L"Idle");

	pStage1->AddObject(3, pPlayer);
	

	// 스크립트 받아오기
	//qCameraMoveScript* camScript = nullptr;
	//const vector<qScript*>& vecScripts = CameraObject->GetScripts();
	//for (size_t i = 0; i < vecScripts.size(); ++i)
	//{
	//	if (vecScripts[i]->GetComponentType() == COMPONENT_TYPE::SCRIPT)
	//	{
	//		camScript = (qCameraMoveScript*)vecScripts[i];
	//		break;
	//	}
	//}
	//if (camScript != nullptr)
	//	camScript->SetFollowObject(pPlayer);
	



	// Monster Object
	qGameObject* pMonster = new qGameObject;
	pMonster->SetName(L"Monster");

	pMonster->AddComponent(new qTransform);
	pMonster->AddComponent(new qMeshRender);
	pMonster->AddComponent(new qCollider2D);

	pMonster->Transform()->SetRelativePos(-400.f, 0.f, 10.f);
	pMonster->Transform()->SetRelativeScale(150.f, 150.f, 1.f);

	pMonster->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pMonster->Collider2D()->SetScale(Vec3(1.2f, 1.2f, 1.f));


	pMonster->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pMonster->MeshRender()->SetMaterial(pMtrl);

	pStage1->AddObject(4, pMonster);



	// 레벨 시작
	ChangeLevel(pStage1, LEVEL_STATE::STOP);


	// 충돌 지정
	qCollisionMgr::GetInst()->CollisionCheck(2, 3);		// Player vs Platform
}

void qLevel_stage1::CreatePrefab()
{
}
