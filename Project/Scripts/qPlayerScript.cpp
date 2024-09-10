#include "pch.h"
#include "qPlayerScript.h"
#include "qMissileScript.h"
#include "qBookScript_Left.h"
#include "qBookScript_Right.h"
#include "qComboScript.h"
#include "qPostScript.h"
#include "States/qPostCloseState.h"


#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>
#include <Engine/qRigidBody.h>
#include <Engine/qScript.h>
#include <Engine/qState.h>

#include <States/qStateMgr.h>
#include <Engine/qStateMachine.h>

qPlayerScript::qPlayerScript()
	: qScript(SCRIPT_TYPE::PLAYERSCRIPT)
	, m_Speed(500.f)
	, m_DirChanged(false)
	, m_Dir(0.f)
	, m_PlayerDir(DIRECTION::RIGHT)
	, m_CurJumpCount(0)
	, m_DoubleJumpCount(2)
	, m_DirLock(false)
	, m_IsDash(false)
	, m_DashCoolTime(0.f)
	, m_IsDashCoolTime(false)
	, m_NextCombo(1)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, "PlayerSpeed", &m_Speed);
	AddScriptParam(SCRIPT_PARAM::TEXTURE, "Test", &m_Texture);
	AddScriptParam(SCRIPT_PARAM::PREFAB, "Missile", &m_MissilePref);
	AddScriptParam(SCRIPT_PARAM::PREFAB, "BookPref", &m_BookPref);
}

qPlayerScript::~qPlayerScript()
{
}

void qPlayerScript::PlayCombo()
{
	if (m_NextCombo == 1)
	{
		FSM()->ChangeState(L"Combo1");
	}
	else if (m_NextCombo == 2)
	{
		FSM()->ChangeState(L"Combo2");
	}
	else if (m_NextCombo == 3)
	{
		FSM()->ChangeState(L"Combo3");
	}
	else if (m_NextCombo == 4)
	{
		FSM()->ChangeState(L"Combo4");
	}
	else
	{
		return;
	}

	++m_NextCombo;

}

void qPlayerScript::Jump()
{
	RigidBody()->jump();
}



void qPlayerScript::Begin()
{
	m_PrevUnitInfo = m_CurUnitInfo;

	GetRenderComponent()->GetDynamicMaterial();

	//SetPlayerState(PLAYER_STATE::IDLE);
	SetPlayerDir(DIRECTION::RIGHT);
	SetDir(DIRECTION::RIGHT);

	if (GetPlayerDir() == DIRECTION::RIGHT)
	{
		m_Dir = 1.f;
	}
	else if (GetPlayerDir() == DIRECTION::LEFT)
	{
		m_Dir = -1.f;
	}

	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	if (pCurLevel->GetName() == L"stage1")
	{
		FSM()->ChangeState(L"Idle");
		//FlipBookComponent()->Play(0, 10, false);
	}

	if (pCurLevel->GetName() == L"stage2")
	{
		//RigidBody()->SetGround(true);
		//FlipBookComponent()->Play(25, 10, false);
		FSM()->ChangeState(L"Null");
	}

	if (pCurLevel->GetName() == L"stageboss")
	{
		
		//FlipBookComponent()->Play(0, 10, false);
		FSM()->ChangeState(L"Null");
	}

	

	//m_PlayerPos = Transform()->GetRelativePos();
	//m_PlayerRot = Transform()->GetRelativeRotation();

	//m_MissilePref = qAssetMgr::GetInst()->FindAsset<qPrefab>(L"MissilePref");
}

void qPlayerScript::Tick()
{
	m_PrevUnitInfo = m_CurUnitInfo;

	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vRot = Transform()->GetRelativeRotation();

	// 다음 프레임 방향 설정
	if (KEY_TAP(KEY::LEFT) || KEY_PRESSED(KEY::LEFT))
	{
		m_CurUnitInfo.Dir = DIRECTION::LEFT;
		m_PlayerDir = DIRECTION::LEFT;
		SetDir(DIRECTION::LEFT);
		vRot.y = 3.141592f;
		vPos.x -= DT * m_Speed;
	}

	if (KEY_TAP(KEY::RIGHT) || KEY_PRESSED(KEY::RIGHT))
	{
		m_CurUnitInfo.Dir = DIRECTION::RIGHT;
		m_PlayerDir = DIRECTION::RIGHT;
		SetDir(DIRECTION::RIGHT);
		vRot.y = 0.f;
		vPos.x += DT * m_Speed;
	}

	if (KEY_TAP(KEY::SPACE))
	{
		if (m_DoubleJumpCount > m_CurJumpCount)
		{
			Jump();

			m_CurJumpCount += 1;
		}
	}

	if (KEY_TAP(KEY::A))
	{
		PlayCombo();
	}

	if (KEY_TAP(KEY::S))
	{
		// 왼쪽 책 발사
		if (GetPlayerDir() == DIRECTION::LEFT)
		{
			//Instantiate(m_BookPref, 4, Transform()->GetWorldPos(), L"Book");
			Ptr<qMaterial> pMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DMtrl");

			qGameObject* pPlayer = qLevelMgr::GetInst()->FindObjectByName(L"Player");
			Vec3 vPlayerPos = pPlayer->Transform()->GetRelativePos();

			LeftBook = new qGameObject;
			LeftBook->SetName(L"LeftBookHitBox");
			LeftBook->AddComponent(new qBookScript_Left);
			LeftBook->AddComponent(new qTransform);
			LeftBook->Transform()->SetRelativeScale(70.f, 70.f, 1.f);
			LeftBook->Transform()->SetRelativePos(Vec3(vPlayerPos.x - 30.f, vPlayerPos.y, vPlayerPos.z));

			LeftBook->AddComponent(new qMeshRender);
			LeftBook->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
			LeftBook->MeshRender()->SetMaterial(pMtrl);

			LeftBook->AddComponent(new qCollider2D);
			LeftBook->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

			LeftBook->AddComponent(new qFlipBookComponent);
			
			Ptr<qFlipBook> pBookFlip = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\book.flip");
			LeftBook->FlipBookComponent()->AddFlipBook(18, pBookFlip);

			LeftBook->FlipBookComponent()->Play(18, 15, true);

			qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
			pCurLevel->AddObject(4, LeftBook);
		}

		// 오른쪽 책 발사
		else if (GetPlayerDir() == DIRECTION::RIGHT)
		{
			Ptr<qMaterial> pMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DMtrl");

			qGameObject* pPlayer = qLevelMgr::GetInst()->FindObjectByName(L"Player");
			Vec3 vPlayerPos = pPlayer->Transform()->GetRelativePos();

			RightBook = new qGameObject;
			RightBook->SetName(L"RightBookHitBox");
			RightBook->AddComponent(new qBookScript_Right);
			RightBook->AddComponent(new qTransform);
			RightBook->Transform()->SetRelativeScale(70.f, 70.f, 1.f);
			RightBook->Transform()->SetRelativePos(Vec3(vPlayerPos.x + 30.f, vPlayerPos.y, vPlayerPos.z));

			RightBook->AddComponent(new qMeshRender);
			RightBook->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
			RightBook->MeshRender()->SetMaterial(pMtrl);

			RightBook->AddComponent(new qCollider2D);
			RightBook->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

			RightBook->AddComponent(new qFlipBookComponent);

			Ptr<qFlipBook> pBookFlip = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\book.flip");
			RightBook->FlipBookComponent()->AddFlipBook(18, pBookFlip);

			RightBook->FlipBookComponent()->Play(18, 15, true);

			qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
			pCurLevel->AddObject(4, RightBook);
		}
	}





	//qLevel* pLevel = qLevelSaveLoad::LoadLevel(L"level\\stage1test.lv");
	//qLevelMgr::GetInst()->ChangeLevel(pLevel);



	Transform()->SetRelativePos(vPos);
	Transform()->SetRelativeRotation(vRot);


	// 다음 프레임에 방향이 바뀌는지
	if (m_CurUnitInfo.Dir != m_PrevUnitInfo.Dir)
	{
		m_DirChanged = true;
	}
	else
	{
		m_DirChanged = false;
	}

	// 대쉬를 사용 했는지
	if (m_IsDash)
	{
		m_DashCoolTime += DT;
	}

	if (m_DashCoolTime > 0.5f)
	{
		m_DashCoolTime = 0.f;
		m_IsDashCoolTime = false;
		m_IsDash = false;
	}


	if (RigidBody()->IsGround())
	{
		m_CurJumpCount = 0;
	}

	// 애니메이션 방향정보 갱신
	GetRenderComponent()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, (int)m_CurUnitInfo.Dir);

	


	//if (KEY_PRESSED(KEY::Z))
	//{
	//	MeshRender()->GetMaterial()->SetScalarParam(INT_0, 1);
	//	Vec3 vRot = Transform()->GetRelativeRotation();
	//	vRot.z += DT * XM_PI;
	//	Transform()->SetRelativeRotation(vRot);
	//
	//
	//	//Vec3 vScale = Transform()->GetRelativeScale();
	//	//vScale += DT * 100.f * Vec3(1.f, 1.f, 1.f);
	//	//Transform()->SetRelativeScale(vScale);
	//}
	//else
	//{
	//	//MeshRender()->GetMaterial()->SetScalarParam(INT_0, 0);
	//}

	//if (KEY_TAP(KEY::SPACE))
	//{
	//	if (nullptr != m_MissilePref)
	//	{
	//		Instantiate(m_MissilePref, 5, Transform()->GetWorldPos(), L"Missile");
	//	}
	//
	//	//// 미사일 발사
	//	//qGameObject* pMissileObject = new qGameObject;
	//	//pMissileObject->AddComponent(new qTransform);
	//	//pMissileObject->AddComponent(new qMeshRender);
	//	//pMissileObject->AddComponent(new qCollider2D);
	//	//pMissileObject->AddComponent(new qMissileScript);
	//
	//	//Vec3 vMissilePos = Transform()->GetRelativePos();
	//	//vMissilePos.y += Transform()->GetRelativeScale().y / 2.f;
	//
	//	//pMissileObject->Transform()->SetRelativePos(vMissilePos);
	//	//pMissileObject->Transform()->SetRelativeScale(Vec3(50.f, 50.f, 1.f));
	//
	//	//pMissileObject->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
	//
	//	//CreateObject(pMissileObject, 5);
	//}


}



void qPlayerScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
	//if (_OtherObject->GetName() == L"Platform")
	//{
	//	qRigidBody* pRB = _OtherObject->GetComponent(COMPONENT_TYPE::RIGIDBODY)->RigidBody();
	//
	//	pRB->SetGround(true);
	//
	//
	//}

	//DeleteObject(_OtherObject);

	//Vec3 vScale = Transform()->GetRelativeScale();
	//
	//vScale += Vec3(10.f, 10.f, 0.f);
	//Collider2D()->SetScale(Collider2D()->GetScale() + Vec3(10.f, 10.f, 0.f));
	//
	//Transform()->SetRelativeScale(vScale);

	if (_OtherObject->GetName() == L"Wall")
	{
		FSM()->ChangeState(L"Bump");
	}
}

void qPlayerScript::Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
	//qLevelMgr::GetInst()->ChangeLevel(L"stage1");

	if (_OtherObject->GetName() == L"Door")
	{
		if (KEY_TAP(KEY::UP))
		{
			FSM()->ChangeState(L"Teleport");
		}
	}

	if (_OtherObject->GetName() == L"Elevator2")
	{
		if (KEY_TAP(KEY::UP))
		{
			FSM()->ChangeState(L"Teleport");
		}
	}
}

void qPlayerScript::EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}



void qPlayerScript::SaveToFile(FILE* _File)
{
	fwrite(&m_Speed, sizeof(float), 1, _File);
	SaveAssetRef(m_Texture, _File);
	SaveAssetRef(m_BookPref, _File);
}

void qPlayerScript::LoadFromFile(FILE* _File)
{
	fread(&m_Speed, sizeof(float), 1, _File);
	LoadAssetRef(m_Texture, _File);
	LoadAssetRef(m_BookPref, _File);
}

