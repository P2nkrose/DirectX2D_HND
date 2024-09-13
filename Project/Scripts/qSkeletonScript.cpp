#include "pch.h"
#include "qSkeletonScript.h"

#include "qPlayerScript.h"
#include "qPlatformScript.h"

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>
#include <Engine/qRigidBody.h>
#include <Engine/qScript.h>
#include <Engine/qState.h>

#include <States/qStateMgr.h>

qSkeletonScript::qSkeletonScript()
	: qScript((UINT)SCRIPT_TYPE::SKELETONSCRIPT)
	, m_DirChanged(false)
	, m_SkeletonDir(DIRECTION::LEFT)
{
}

qSkeletonScript::~qSkeletonScript()
{
}

void qSkeletonScript::Begin()
{
	m_PrevUnitInfo = m_CurUnitInfo;

	m_CurUnitInfo.HP = 50.f;
	SetSkeletonDir(DIRECTION::LEFT);

	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();

	if (pCurLevel->GetName() == L"stage2")
	{
		// idle
	}

}

void qSkeletonScript::Tick()
{
	m_PrevUnitInfo = m_CurUnitInfo;

	// 방향 세팅
	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vRot = Transform()->GetRelativeRotation();
	if (m_CurUnitInfo.Dir == DIRECTION::LEFT)
		vRot.y = 0.f;
	else if (m_CurUnitInfo.Dir == DIRECTION::RIGHT)
		vRot.y = 3.141592f;

	// HP 세팅
	float CurDamage = m_PrevUnitInfo.HP - m_CurUnitInfo.HP;

	static bool flag = false;

	if (m_CurUnitInfo.HP <= 0 && !flag)
	{
		GetOwner()->FSM()->ChangeState(L"SkeletonDeath");

		flag = true;
	}

	// Anim 방향 정보 갱신 -1: Left , 1: Right
	GetRenderComponent()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, (int)m_CurUnitInfo.Dir);
}

void qSkeletonScript::Hit(float _Damage)
{
	const wstring& CurState = qStateMgr::GetStateName(GetOwner()->FSM()->GetCurState());

	if (CurState == L"qSkeletonDeathState")
		return;

	m_CurUnitInfo.HP -= _Damage;
}

void qSkeletonScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Player")
	{
		_OtherObject->FSM()->ChangeState(L"Bump");
	}

	qPlayerScript* PlayerScript = _OtherObject->GetScript<qPlayerScript>();

	if (PlayerScript == nullptr)
		return;

	// 플레이어 피깎기

}

void qSkeletonScript::Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qSkeletonScript::EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qSkeletonScript::SaveToFile(FILE* _File)
{
}

void qSkeletonScript::LoadFromFile(FILE* _File)
{
}


