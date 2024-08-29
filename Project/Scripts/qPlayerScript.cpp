#include "pch.h"
#include "qPlayerScript.h"
#include "qMissileScript.h"

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

	if (GetPlayerDir() == DIRECTION::RIGHT)
	{
		m_Dir = 1.f;
	}
	else if (GetPlayerDir() == DIRECTION::LEFT)
	{
		m_Dir = -1.f;
	}

	FlipBookComponent()->Play(0, 10, true);

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
		vRot.y = 3.141592f;
		vPos.x -= DT * m_Speed;
	}

	if (KEY_TAP(KEY::RIGHT) || KEY_PRESSED(KEY::RIGHT))
	{
		m_CurUnitInfo.Dir = DIRECTION::RIGHT;
		m_PlayerDir = DIRECTION::RIGHT;
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
		//FSM()->ChangeState(L"Combo1");
		PlayCombo();
	}



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
}

void qPlayerScript::Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qPlayerScript::EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}



void qPlayerScript::SaveToFile(FILE* _File)
{
	fwrite(&m_Speed, sizeof(float), 1, _File);
	SaveAssetRef(m_Texture, _File);
	SaveAssetRef(m_MissilePref, _File);
}

void qPlayerScript::LoadFromFile(FILE* _File)
{
	fread(&m_Speed, sizeof(float), 1, _File);
	LoadAssetRef(m_Texture, _File);
	LoadAssetRef(m_MissilePref, _File);
}

