#include "pch.h"
#include "qLevel_stage2.h"


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

#include <Engine/qSetColorCS.h>
#include <Engine/qStructuredBuffer.h>

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
#include <States/qPlayerHitState.h>				// 11

#include <States/qPlayerCombo1State.h>			// 13
#include <States/qPlayerCombo2State.h>			// 14
#include <States/qPlayerCombo3State.h>			// 15
#include <States/qPlayerCombo4State.h>			// 16
#include <States/qPlayerBookShootState.h>		// 17

#include <States/qPlayerCrashState.h>			// 19
#include <States/qPlayerRangeState.h>			// 20
#include <States/qPlayerKrushState.h>			// 21


#include "qLevelSaveLoad.h"

void qLevel_stage2::CreateStage2()
{
	// Sound


	// Material
	Ptr<qMaterial> pMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DMtrl");
	Ptr<qMaterial> pAlphaBlendMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DAlphaBlendMtrl");
	Ptr<qMaterial> pDebugShapeMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"DebugShapeMtrl");

	Ptr<qMaterial> pMtrl2 = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"material\\stage2Back.mtrl");

	// Level
	qLevel* pStage2 = new qLevel;

	qLevelMgr::GetInst()->InsertLevel(L"stage2", pStage2);

	pStage2->SetName(L"stage2");

	pStage2->GetLayer(0)->SetName(L"Camera");
	pStage2->GetLayer(1)->SetName(L"Background");
	pStage2->GetLayer(2)->SetName(L"Platform");
	pStage2->GetLayer(3)->SetName(L"Player");
	pStage2->GetLayer(4)->SetName(L"PlayerSkill");
	pStage2->GetLayer(5)->SetName(L"Monster");
	pStage2->GetLayer(6)->SetName(L"MonsterSkill");
	pStage2->GetLayer(7)->SetName(L"Boss");
	pStage2->GetLayer(8)->SetName(L"BossSkill");
	pStage2->GetLayer(9)->SetName(L"Portal");
	pStage2->GetLayer(10)->SetName(L"Light");
	pStage2->GetLayer(31)->SetName(L"UI");

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


	pStage2->AddObject(0, CameraObject);

	// 배경
	qGameObject* pBackground = new qGameObject;
	pBackground->SetName(L"BGstage2");

	pBackground->AddComponent(new qTransform);
	pBackground->Transform()->SetRelativePos(0.f, 0.f, 50.f);
	pBackground->Transform()->SetRelativeScale(11482.f, 1789.f, 1.f);

	pBackground->AddComponent(new qMeshRender);
	pBackground->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
	pBackground->MeshRender()->SetMaterial(pMtrl2);

	pStage2->AddObject(1, pBackground);


	// ============
	//   Platform
	// ============

	// Platform 1
	qGameObject* pPlatform1 = new qGameObject;
	pPlatform1->SetName(L"Platform");
	pPlatform1->AddComponent(new qPlatformScript);
	pPlatform1->AddComponent(new qTransform);
	pPlatform1->Transform()->SetRelativePos(-5028.f, -271.f, 10.f);
	pPlatform1->Transform()->SetRelativeScale(1427.f, 15.f, 1.f);
	pPlatform1->AddComponent(new qCollider2D);
	pPlatform1->Collider2D()->SetIndependentScale(false);
	pPlatform1->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform1->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform1);

	// Platform 2
	qGameObject* pPlatform2 = new qGameObject;
	pPlatform2->SetName(L"Platform");
	pPlatform2->AddComponent(new qPlatformScript);
	pPlatform2->AddComponent(new qTransform);
	pPlatform2->Transform()->SetRelativePos(-5092.f, -615.f, 10.f);
	pPlatform2->Transform()->SetRelativeScale(1302.f, 15.f, 1.f);
	pPlatform2->AddComponent(new qCollider2D);
	pPlatform2->Collider2D()->SetIndependentScale(false);
	pPlatform2->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform2->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform2);

	// Platform 3
	qGameObject* pPlatform3 = new qGameObject;
	pPlatform3->SetName(L"Platform");
	pPlatform3->AddComponent(new qPlatformScript);
	pPlatform3->AddComponent(new qTransform);
	pPlatform3->Transform()->SetRelativePos(-3920.f, -153.f, 10.f);
	pPlatform3->Transform()->SetRelativeScale(502.f, 15.f, 1.f);
	pPlatform3->AddComponent(new qCollider2D);
	pPlatform3->Collider2D()->SetIndependentScale(false);
	pPlatform3->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform3->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform3);

	// Platform 4
	qGameObject* pPlatform4 = new qGameObject;
	pPlatform4->SetName(L"Platform");
	pPlatform4->AddComponent(new qPlatformScript);
	pPlatform4->AddComponent(new qTransform);
	pPlatform4->Transform()->SetRelativePos(-4061.f, -667.f, 10.f);
	pPlatform4->Transform()->SetRelativeScale(745.f, 15.f, 1.f);
	pPlatform4->AddComponent(new qCollider2D);
	pPlatform4->Collider2D()->SetIndependentScale(false);
	pPlatform4->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform4->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform4);

	// Platform 5
	qGameObject* pPlatform5 = new qGameObject;
	pPlatform5->SetName(L"Platform");
	pPlatform5->AddComponent(new qPlatformScript);
	pPlatform5->AddComponent(new qTransform);
	pPlatform5->Transform()->SetRelativePos(-3385.f, -469.f, 10.f);
	pPlatform5->Transform()->SetRelativeScale(698.f, 15.f, 1.f);
	pPlatform5->AddComponent(new qCollider2D);
	pPlatform5->Collider2D()->SetIndependentScale(false);
	pPlatform5->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform5->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform5);

	// Platform 6
	qGameObject* pPlatform6 = new qGameObject;
	pPlatform6->SetName(L"Platform");
	pPlatform6->AddComponent(new qPlatformScript);
	pPlatform6->AddComponent(new qTransform);
	pPlatform6->Transform()->SetRelativePos(-2966.f, -153.f, 10.f);
	pPlatform6->Transform()->SetRelativeScale(501.f, 15.f, 1.f);
	pPlatform6->AddComponent(new qCollider2D);
	pPlatform6->Collider2D()->SetIndependentScale(false);
	pPlatform6->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform6->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform6);

	// Platform 7
	qGameObject* pPlatform7 = new qGameObject;
	pPlatform7->SetName(L"Platform");
	pPlatform7->AddComponent(new qPlatformScript);
	pPlatform7->AddComponent(new qTransform);
	pPlatform7->Transform()->SetRelativePos(-2266.f, 204.f, 10.f);
	pPlatform7->Transform()->SetRelativeScale(1224.f, 15.f, 1.f);
	pPlatform7->AddComponent(new qCollider2D);
	pPlatform7->Collider2D()->SetIndependentScale(false);
	pPlatform7->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform7->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform7);

	// Platform 8
	qGameObject* pPlatform8 = new qGameObject;
	pPlatform8->SetName(L"Platform");
	pPlatform8->AddComponent(new qPlatformScript);
	pPlatform8->AddComponent(new qTransform);
	pPlatform8->Transform()->SetRelativePos(-1870.f, -156.f, 10.f);
	pPlatform8->Transform()->SetRelativeScale(1427.f, 15.f, 1.f);
	pPlatform8->AddComponent(new qCollider2D);
	pPlatform8->Collider2D()->SetIndependentScale(false);
	pPlatform8->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform8->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform8);


	// Platform 9
	qGameObject* pPlatform9 = new qGameObject;
	pPlatform9->SetName(L"Platform");
	pPlatform9->AddComponent(new qPlatformScript);
	pPlatform9->AddComponent(new qTransform);
	pPlatform9->Transform()->SetRelativePos(-991.f, 64.f, 10.f);
	pPlatform9->Transform()->SetRelativeScale(633.f, 15.f, 1.f);
	pPlatform9->AddComponent(new qCollider2D);
	pPlatform9->Collider2D()->SetIndependentScale(false);
	pPlatform9->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform9->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform9);

	// Platform 10
	qGameObject* pPlatform10 = new qGameObject;
	pPlatform10->SetName(L"Platform");
	pPlatform10->AddComponent(new qPlatformScript);
	pPlatform10->AddComponent(new qTransform);
	pPlatform10->Transform()->SetRelativePos(-253.f, -70.f, 10.f);
	pPlatform10->Transform()->SetRelativeScale(566.f, 15.f, 1.f);
	pPlatform10->AddComponent(new qCollider2D);
	pPlatform10->Collider2D()->SetIndependentScale(false);
	pPlatform10->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform10->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform10);

	// Platform 11
	qGameObject* pPlatform11 = new qGameObject;
	pPlatform11->SetName(L"Platform");
	pPlatform11->AddComponent(new qPlatformScript);
	pPlatform11->AddComponent(new qTransform);
	pPlatform11->Transform()->SetRelativePos(-592.f, -434.f, 10.f);
	pPlatform11->Transform()->SetRelativeScale(884.f, 15.f, 1.f);
	pPlatform11->AddComponent(new qCollider2D);
	pPlatform11->Collider2D()->SetIndependentScale(false);
	pPlatform11->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform11->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform11);

	// Platform 12
	qGameObject* pPlatform12 = new qGameObject;
	pPlatform12->SetName(L"Platform");
	pPlatform12->AddComponent(new qPlatformScript);
	pPlatform12->AddComponent(new qTransform);
	pPlatform12->Transform()->SetRelativePos(70.f, -290.f, 10.f);
	pPlatform12->Transform()->SetRelativeScale(499.f, 15.f, 1.f);
	pPlatform12->AddComponent(new qCollider2D);
	pPlatform12->Collider2D()->SetIndependentScale(false);
	pPlatform12->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform12->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform12);

	// Platform 13
	qGameObject* pPlatform13 = new qGameObject;
	pPlatform13->SetName(L"Platform");
	pPlatform13->AddComponent(new qPlatformScript);
	pPlatform13->AddComponent(new qTransform);
	pPlatform13->Transform()->SetRelativePos(773.f, 32.f, 10.f);
	pPlatform13->Transform()->SetRelativeScale(1276.f, 15.f, 1.f);
	pPlatform13->AddComponent(new qCollider2D);
	pPlatform13->Collider2D()->SetIndependentScale(false);
	pPlatform13->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform13->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform13);

	// Platform 14
	qGameObject* pPlatform14 = new qGameObject;
	pPlatform14->SetName(L"Platform");
	pPlatform14->AddComponent(new qPlatformScript);
	pPlatform14->AddComponent(new qTransform);
	pPlatform14->Transform()->SetRelativePos(894.f, -292.f, 10.f);
	pPlatform14->Transform()->SetRelativeScale(861.f, 15.f, 1.f);
	pPlatform14->AddComponent(new qCollider2D);
	pPlatform14->Collider2D()->SetIndependentScale(false);
	pPlatform14->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform14->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform14);


	// Platform 15
	qGameObject* pPlatform15 = new qGameObject;
	pPlatform15->SetName(L"Platform");
	pPlatform15->AddComponent(new qPlatformScript);
	pPlatform15->AddComponent(new qTransform);
	pPlatform15->Transform()->SetRelativePos(1596.f, -504.f, 10.f);
	pPlatform15->Transform()->SetRelativeScale(557.f, 15.f, 1.f);
	pPlatform15->AddComponent(new qCollider2D);
	pPlatform15->Collider2D()->SetIndependentScale(false);
	pPlatform15->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform15->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform15);

	// Platform 16
	qGameObject* pPlatform16 = new qGameObject;
	pPlatform16->SetName(L"Platform");
	pPlatform16->AddComponent(new qPlatformScript);
	pPlatform16->AddComponent(new qTransform);
	pPlatform16->Transform()->SetRelativePos(2982.f, -10.f, 10.f);
	pPlatform16->Transform()->SetRelativeScale(605.f, 15.f, 1.f);
	pPlatform16->AddComponent(new qCollider2D);
	pPlatform16->Collider2D()->SetIndependentScale(false);
	pPlatform16->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform16->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform16);

	// Platform 17
	qGameObject* pPlatform17 = new qGameObject;
	pPlatform17->SetName(L"Platform");
	pPlatform17->AddComponent(new qPlatformScript);
	pPlatform17->AddComponent(new qTransform);
	pPlatform17->Transform()->SetRelativePos(3848.f, -10.f, 10.f);
	pPlatform17->Transform()->SetRelativeScale(605.f, 15.f, 1.f);
	pPlatform17->AddComponent(new qCollider2D);
	pPlatform17->Collider2D()->SetIndependentScale(false);
	pPlatform17->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform17->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform17);

	// Platform 18
	qGameObject* pPlatform18 = new qGameObject;
	pPlatform18->SetName(L"Platform");
	pPlatform18->AddComponent(new qPlatformScript);
	pPlatform18->AddComponent(new qTransform);
	pPlatform18->Transform()->SetRelativePos(3810.f, -298.f, 10.f);
	pPlatform18->Transform()->SetRelativeScale(3886.f, 15.f, 1.f);
	pPlatform18->AddComponent(new qCollider2D);
	pPlatform18->Collider2D()->SetIndependentScale(false);
	pPlatform18->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlatform18->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	pStage2->AddObject(2, pPlatform18);


	// 광원 오브젝트
	qGameObject* pLight = new qGameObject;
	pLight->SetName(L"PointLight 2");
	pLight->AddComponent(new qTransform);
	pLight->AddComponent(new qLight2D);

	pLight->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	pLight->Light2D()->SetLightColor(Vec3(1.f, 1.f, 1.f));
	pLight->Light2D()->SetRadius(1000.f);

	pStage2->AddObject(0, pLight);


	// 플레이어 오브젝트 
	qGameObject* pPlayer = new qGameObject;
	pPlayer->SetName(L"Player");
	pPlayer->AddComponent(new qPlayerScript);
	//pPlayer->AddChild(pLight);

	pPlayer->AddComponent(new qTransform);
	pPlayer->Transform()->SetRelativePos(-5028.f, 0.f, 10.f);
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

	Ptr<qFlipBook> pDeathHit = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\hit.flip");
	pPlayer->FlipBookComponent()->AddFlipBook(11, pDeathHit);

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
	pPlayer->FSM()->AddState(L"Hit", new qPlayerHitState);					// 11

	pPlayer->FSM()->AddState(L"Combo1", new qPlayerCombo1State);			// 13
	pPlayer->FSM()->AddState(L"Combo2", new qPlayerCombo2State);			// 14
	pPlayer->FSM()->AddState(L"Combo3", new qPlayerCombo3State);			// 15
	pPlayer->FSM()->AddState(L"Combo4", new qPlayerCombo4State);			// 16
	pPlayer->FSM()->AddState(L"BookShoot", new qPlayerBookShootState);		// 17

	pPlayer->FSM()->AddState(L"Crash", new qPlayerCrashState);				// 19
	pPlayer->FSM()->AddState(L"Range", new qPlayerRangeState);				// 20
	pPlayer->FSM()->AddState(L"Krush", new qPlayerKrushState);				// 21

	pPlayer->FSM()->ChangeState(L"Idle");

	pStage2->AddObject(3, pPlayer);


	// 충돌 지정
	qCollisionMgr::GetInst()->CollisionCheck(2, 3);		// Player vs Platform
	qCollisionMgr::GetInst()->CollisionCheck(3, 5);		// Player vs Monster
	qCollisionMgr::GetInst()->CollisionCheck(3, 9);		// Player vs Portal

	ChangeLevel(pStage2, LEVEL_STATE::STOP);

}
