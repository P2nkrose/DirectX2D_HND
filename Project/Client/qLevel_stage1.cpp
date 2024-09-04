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
#include <Engine/qTaskMgr.h>

#include <Engine/qLevel.h>
#include <Engine/qLayer.h>
#include <Engine/qGameObject.h>
#include <Engine/components.h>

#include <Scripts/qPlayerScript.h>
#include <Scripts/qBookScript_Left.h>
#include <Scripts/qMissileScript.h>
#include <Scripts/qCameraMoveScript.h>
#include <Scripts/qPlatformScript.h>
#include <Scripts/qPortalScript.h>
#include <Scripts/qDoorScript.h>
#include <Scripts/qPostScript.h>

#include <Engine/qSetColorCS.h>
#include <Engine/qStructuredBuffer.h>

// ========================                    
//      Player State                         * INDEX *
// ========================

#include <States/qStateMgr.h>
#include <States/qPlayerIdleState.h>			// 0
#include <States/qPlayerWaitState.h>			// 1
#include <States/qPlayerRunState.h>				// 2
#include <States/qPlayerIdleToRunState.h>		// 3
#include <States/qPlayerRunToIdleState.h>		// 4
#include <States/qPlayerIdleUTurnState.h>		// 5
#include <States/qPlayerRunUTurnState.h>		// 6
#include <States/qPlayerJumpState.h>			// 7
#include <States/qPlayerFallingState.h>			// 8
#include <States/qPlayerLandingState.h>			// 9
#include <States/qPlayerDashState.h>			// 10
												// 11

#include <States/qPlayerCombo1State.h>			// 13
#include <States/qPlayerCombo2State.h>			// 14
#include <States/qPlayerCombo3State.h>			// 15
#include <States/qPlayerCombo4State.h>			// 16
#include <States/qPlayerBookShootState.h>		// 17

#include <States/qPlayerCrashState.h>			// 19
#include <States/qPlayerRangeState.h>			// 20
#include <States/qPlayerKrushState.h>			// 21
#include <States/qPlayerTeleportState.h>		// 22
#include <States/qPlayerTeleportFinishState.h>	// 23
#include <States/qPlayerBumpState.h>			// 24


// ========================                    
//      Transfer State                         * INDEX *
// ========================


#include <States/qDoorStayState.h>				// 1
#include <States/qDoorOpenState.h>				// 2
#include <States/qDoorCloseState.h>				// 3

#include <States/qPostCloseState.h>				// 4
#include <States/qPostOpenState.h>				// 5


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

	qLevelMgr::GetInst()->InsertLevel(L"stage1", pStage1);

	pStage1->SetName(L"stage1");

	pStage1->GetLayer(0)->SetName(L"Camera");
	pStage1->GetLayer(1)->SetName(L"Background");
	pStage1->GetLayer(2)->SetName(L"Platform");
	pStage1->GetLayer(3)->SetName(L"Player");
	pStage1->GetLayer(4)->SetName(L"PlayerSkill");
	pStage1->GetLayer(5)->SetName(L"Monster");
	pStage1->GetLayer(6)->SetName(L"MonsterSkill");
	pStage1->GetLayer(7)->SetName(L"Boss");
	pStage1->GetLayer(8)->SetName(L"BossSkill");
	pStage1->GetLayer(9)->SetName(L"Transfer");
	pStage1->GetLayer(31)->SetName(L"UI");


	// Camera
	qGameObject* CameraObject = new qGameObject;
	CameraObject->SetName(L"MainCamera");
	CameraObject->AddComponent(new qCameraMoveScript);
	CameraObject->AddComponent(new qCamera);
	CameraObject->AddComponent(new qTransform);

	// 우선순위를 0 : Main Camera 로 설정
	CameraObject->Camera()->SetPriority(0);

	// 카메라 레이어 설정
	CameraObject->Camera()->SetLayerAll();
	CameraObject->Camera()->SetFar(100000.f);
	CameraObject->Camera()->SetScale(1.0f);
	CameraObject->Camera()->SetProjType(ORTHOGRAPHIC);		// 직교 투영


	pStage1->AddObject(0, CameraObject);


	// 배경
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
	// Collider WorldPos로 해야됨
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
	pPlayer->Transform()->SetRelativePos(0.f, -420.f, 10.f);
	pPlayer->Transform()->SetRelativeScale(130.f, 130.f, 1.f);

	pPlayer->AddComponent(new qMeshRender);
	pPlayer->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pPlayer->MeshRender()->SetMaterial(pMtrl);

	pPlayer->AddComponent(new qFlipBookComponent);
	
	Ptr<qFlipBook> pDeathIdle = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\death_idle_right.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(0, pDeathIdle);

	Ptr<qFlipBook> pDeathWait = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\wait.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(1, pDeathWait);

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

	Ptr<qFlipBook> pDeathBookShoot = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\bookshoot.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(17, pDeathBookShoot);

	Ptr<qFlipBook> pDeathCrash = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\crash_final.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(19, pDeathCrash);

	Ptr<qFlipBook> pDeathRange = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\range_test2.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(20, pDeathRange);

	Ptr<qFlipBook> pDeathKrush = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\krush_final.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(21, pDeathKrush);

	Ptr<qFlipBook> pDeathTeleport = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\teleport.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(22, pDeathTeleport);

	Ptr<qFlipBook> pDeathTeleportFinish = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\teleport_finish.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(23, pDeathTeleportFinish);

	Ptr<qFlipBook> pDeathBump = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\hit.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(24, pDeathBump);

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
	pPlayer->FSM()->AddState(L"Wait", new qPlayerWaitState);				// 1
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
	pPlayer->FSM()->AddState(L"BookShoot", new qPlayerBookShootState);		// 17

	pPlayer->FSM()->AddState(L"Crash", new qPlayerCrashState);				// 19
	pPlayer->FSM()->AddState(L"Range", new qPlayerRangeState);				// 20
	pPlayer->FSM()->AddState(L"Krush", new qPlayerKrushState);				// 21
	pPlayer->FSM()->AddState(L"Teleport", new qPlayerTeleportState);		// 22
	pPlayer->FSM()->AddState(L"TeleportFinish", new qPlayerTeleportFinishState);	// 23
	pPlayer->FSM()->AddState(L"Bump", new qPlayerBumpState);				// 24

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
	
	// =============
	//   TRANSFER
	// =============

	qGameObject* pDoor = new qGameObject;
	pDoor->SetName(L"Door");
	pDoor->AddComponent(new qDoorScript);

	pDoor->AddComponent(new qTransform);
	pDoor->Transform()->SetRelativePos(875.f, -352.f, 10.f);
	pDoor->Transform()->SetRelativeScale(268.f, 265.f, 1.f);

	pDoor->AddComponent(new qMeshRender);
	pDoor->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pDoor->MeshRender()->SetMaterial(pMtrl);

	pDoor->AddComponent(new qFlipBookComponent);
	
	Ptr<qFlipBook> pDoorStay = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\doorstay3.flip");
	pDoor->FlipBookComponent()->AddFlipBook(1, pDoorStay);

	Ptr<qFlipBook> pDoorOpen = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\dooropen.flip");
	pDoor->FlipBookComponent()->AddFlipBook(2, pDoorOpen);

	Ptr<qFlipBook> pDoorClose = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\doorclose.flip");
	pDoor->FlipBookComponent()->AddFlipBook(3, pDoorClose);

	pDoor->FlipBookComponent()->Play(1, 10, true);

	pDoor->AddComponent(new qCollider2D);
	pDoor->Collider2D()->SetIndependentScale(false);
	pDoor->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pDoor->Collider2D()->SetScale(Vec3(0.5f, 1.f, 1.f));

	pDoor->AddComponent(new qFSM);

	pDoor->FSM()->AddState(L"DoorStay", new qDoorStayState);		// 24
	pDoor->FSM()->AddState(L"DoorOpen", new qDoorOpenState);		// 25
	pDoor->FSM()->AddState(L"DoorClose", new qDoorCloseState);		// 26
	

	pDoor->FSM()->ChangeState(L"DoorStay");

	pStage1->AddObject(9, pDoor);


	// 포탈 오브젝트
	//qGameObject* pPortal = new qGameObject;
	//pPortal->SetName(L"Portal");
	//pPortal->AddComponent(new qTransform);
	//pPortal->Transform()->SetRelativePos(600.f, -400.f, 10.f);
	//pPortal->Transform()->SetRelativeScale(150.f, 150.f, 1.f);
	//
	//pPortal->AddComponent(new qCollider2D);
	//pPortal->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	//pPortal->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.));
	//
	//pPortal->AddComponent(new qPortalScript);
	//
	//pStage1->AddObject(9, pPortal);



	// Post Process
	qGameObject* pPostProcess = new qGameObject;
	pPostProcess->SetName(L"Post");

	pPostProcess->AddComponent(new qPostScript);
	pPostProcess->AddComponent(new qTransform);
	
	pPostProcess->AddComponent(new qMeshRender);
	pPostProcess->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pPostProcess->MeshRender()->SetMaterial(pMtrl);
	
	pPostProcess->AddComponent(new qFlipBookComponent);
	
	Ptr<qFlipBook> pPostClose = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\chang.flip");
	pPostProcess->FlipBookComponent()->AddFlipBook(4, pPostClose);

	pPostProcess->AddComponent(new qFSM);
	pPostProcess->FSM()->AddState(L"PostClose", new qPostCloseState);
	
	pStage1->AddObject(9, pPostProcess);


	// Monster Object
	qGameObject* pMonster = new qGameObject;
	pMonster->SetName(L"Monster");

	pMonster->AddComponent(new qTransform);
	pMonster->AddComponent(new qMeshRender);
	pMonster->AddComponent(new qCollider2D);

	pMonster->Transform()->SetRelativePos(-400.f, -420.f, 10.f);
	pMonster->Transform()->SetRelativeScale(150.f, 150.f, 1.f);

	pMonster->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pMonster->Collider2D()->SetScale(Vec3(1.2f, 1.2f, 1.f));


	pMonster->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pMonster->MeshRender()->SetMaterial(pMtrl);

	pStage1->AddObject(5, pMonster);


	// Level Save
	//wstring strLevelPath = qPathMgr::GetInst()->GetContentPath();
	//strLevelPath += L"level\\stage1test.lv";
	//qLevelSaveLoad::SaveLevel(strLevelPath, pStage1);

	// 레벨 시작
	ChangeLevel(pStage1, LEVEL_STATE::STOP);


	// 충돌 지정
	qCollisionMgr::GetInst()->CollisionCheck(2, 3);		// Player vs Platform
	qCollisionMgr::GetInst()->CollisionCheck(3, 5);		// Player vs Monster
	qCollisionMgr::GetInst()->CollisionCheck(3, 9);		// Player vs Transfer
	qCollisionMgr::GetInst()->CollisionCheck(3, 11);	// Player vs Wall (Bump)
}

void qLevel_stage1::CreatePrefab()
{
	//Ptr<qMaterial> pMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DMtrl");

	//qGameObject* pBook = new qGameObject;
	//pBook->SetName(L"Book");
	//pBook->AddComponent(new qTransform);
	//pBook->AddComponent(new qBookScript_Left);
	//pBook->Transform()->SetRelativeScale(70.f, 70.f, 1.f);
	//
	//pBook->AddComponent(new qMeshRender);
	//pBook->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	//pBook->MeshRender()->SetMaterial(pMtrl);
	//
	//pBook->AddComponent(new qCollider2D);
	//pBook->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	//
	//pBook->AddComponent(new qFlipBookComponent);
	//
	//Ptr<qFlipBook> pBookFlip = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\book.flip");
	//pBook->FlipBookComponent()->AddFlipBook(18, pBookFlip);
	//
	//Ptr<qPrefab> pPrefab = new qPrefab;
	//pPrefab->SetProtoObject(pBook);
	//
	//qAssetMgr::GetInst()->AddAsset<qPrefab>(L"BookPref", pPrefab);
	//
	//wstring FilePath = qPathMgr::GetInst()->GetContentPath();
	//FilePath += L"prefab\\Book.pref";
	//pPrefab->Save(FilePath);
	
}



