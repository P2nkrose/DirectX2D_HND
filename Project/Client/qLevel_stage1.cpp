#include "pch.h"
#include "qLevel_stage1.h"

#include <Engine/qAssetMgr.h>
#include <Engine/qAsset.h>
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
#include <States/qPlayerJumpState.h>			// 7
#include <States/qPlayerFallingState.h>			// 8
#include <States/qPlayerLandingState.h>			// 9
#include <States/qPlayerDashState.h>			// 10

#include <States/qPlayerCombo1State.h>			// 13
#include <States/qPlayerCombo2State.h>			// 14
#include <States/qPlayerCombo3State.h>			// 15
#include <States/qPlayerCombo4State.h>			// 16


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
	CameraObject->AddComponent(new qCamera);
	CameraObject->AddComponent(new qTransform);

	// �켱������ 0 : Main Camera �� ����
	CameraObject->Camera()->SetPriority(0);

	// ī�޶� ���̾� ����
	CameraObject->Camera()->SetLayerAll();
	CameraObject->Camera()->SetFar(100000.f);
	CameraObject->Camera()->SetScale(1.0f);
	CameraObject->Camera()->SetProjType(ORTHOGRAPHIC);		// ���� ����


	pStage1->AddObject(0, CameraObject);


	// ���
	qGameObject* pBackground = new qGameObject;
	pBackground->SetName(L"BGstage1");
	
	pBackground->AddComponent(new qTransform);
	pBackground->Transform()->SetRelativePos(0.f, 0.f, 50.f);
	pBackground->Transform()->SetRelativeScale(2555.f, 1790.f, 1.f);

	pBackground->AddComponent(new qMeshRender);
	pBackground->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pBackground->MeshRender()->SetMaterial(pMtrl2);

	pStage1->AddObject(1, pBackground);

	// Platform
	// Collider WorldPos�� �ؾߵ�
	qGameObject* pPlatform = new qGameObject;
	pPlatform->SetName(L"Platform");
	pPlatform->AddComponent(new qPlatformScript);

	pPlatform->AddComponent(new qTransform);
	pPlatform->Transform()->SetRelativePos(0.f, -500.f, 10.f);
	pPlatform->Transform()->SetRelativeScale(2560.f, 30.f, 1.f);

	pPlatform->AddComponent(new qCollider2D);
	pPlatform->Collider2D()->SetIndependentScale(false);
	pPlatform->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

	pStage1->AddObject(2, pPlatform);



	// ���� ������Ʈ
	qGameObject* pLight = new qGameObject;
	pLight->SetName(L"PointLight 1");
	pLight->AddComponent(new qTransform);
	pLight->AddComponent(new qLight2D);

	pLight->Light2D()->SetLightType(LIGHT_TYPE::POINT);
	pLight->Light2D()->SetLightColor(Vec3(1.f, 1.f, 1.f));
	pLight->Light2D()->SetRadius(1000.f);

	//pStage1->AddObject(0, pLight);

	



	// �÷��̾� ������Ʈ
	qGameObject* pPlayer = new qGameObject;
	pPlayer->SetName(L"Player");
	pPlayer->AddComponent(new qPlayerScript);
	pPlayer->AddChild(pLight);
	//pPlayer->AddChild(CameraObject);
	

	pPlayer->AddComponent(new qTransform);
	pPlayer->Transform()->SetRelativePos(0.f, -420.f, 10.f);
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

	Ptr<qFlipBook> pDeathJump = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\jump_3.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(7, pDeathJump);

	Ptr<qFlipBook> pDeathFalling = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\falling.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(8, pDeathFalling);

	Ptr<qFlipBook> pDeathLanding = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\landing.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(9, pDeathLanding);

	Ptr<qFlipBook> pDeathDash = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\dash_3.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(10, pDeathDash);

	Ptr<qFlipBook> pDeathCombo1 = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\combo1_final.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(13, pDeathCombo1);

	Ptr<qFlipBook> pDeathCombo2 = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\combo2_final.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(14, pDeathCombo2);

	Ptr<qFlipBook> pDeathCombo3 = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\combo3_f.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(15, pDeathCombo3);

	Ptr<qFlipBook> pDeathCombo4 = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\combo4_finalx.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(16, pDeathCombo4);

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

	// FSM
	pPlayer->AddComponent(new qFSM);

	pPlayer->FSM()->AddState(L"Idle", new qPlayerIdleState);				// 0
	pPlayer->FSM()->AddState(L"Run", new qPlayerRunState);					// 2
	pPlayer->FSM()->AddState(L"IdleToRun", new qPlayerIdleToRunState);		// 3
	pPlayer->FSM()->AddState(L"RunToIdle", new qPlayerRunToIdleState);		// 4
	pPlayer->FSM()->AddState(L"IdleUTurn", new qPlayerIdleUTurnState);		// 5
	pPlayer->FSM()->AddState(L"RunUTurn", new qPlayerRunUTurnState);		// 6
	pPlayer->FSM()->AddState(L"Jump", new qPlayerJumpState);				// 7
	pPlayer->FSM()->AddState(L"Falling", new qPlayerFallingState);			// 8
	pPlayer->FSM()->AddState(L"Landing", new qPlayerLandingState);			// 9
	pPlayer->FSM()->AddState(L"Dash", new qPlayerDashState);				// 10

	pPlayer->FSM()->AddState(L"Combo1", new qPlayerCombo1State);			// 13
	pPlayer->FSM()->AddState(L"Combo2", new qPlayerCombo2State);			// 14
	pPlayer->FSM()->AddState(L"Combo3", new qPlayerCombo3State);			// 15
	pPlayer->FSM()->AddState(L"Combo4", new qPlayerCombo4State);			// 16

	pPlayer->FSM()->ChangeState(L"Idle");

	pStage1->AddObject(3, pPlayer);
	
	
	// ��ũ��Ʈ �޾ƿ���
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



	// ���� ����
	ChangeLevel(pStage1, LEVEL_STATE::STOP);


	// �浹 ����
	qCollisionMgr::GetInst()->CollisionCheck(2, 3);		// Player vs Platform
}

void qLevel_stage1::CreatePrefab()
{
}