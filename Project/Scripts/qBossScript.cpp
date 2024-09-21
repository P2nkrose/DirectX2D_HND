#include "pch.h"
#include "qBossScript.h"

#include "qScriptMgr.h"
#include "qPlayerScript.h"
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>
#include <Engine/qScript.h>
#include <Engine/qState.h>
#include <States/qStateMgr.h>

qBossScript::qBossScript()
	: qScript((UINT)SCRIPT_TYPE::BOSSSCRIPT)
	, m_BangTime(0.f)
	, m_BossDir(DIRECTION::LEFT)
	, m_DirChanged(false)
	, m_Speed(200.f)
	, m_BossColiisionDamage(5.f)
{
}

qBossScript::~qBossScript()
{
}

void qBossScript::Begin()
{
	m_PrevUnitInfo = m_CurUnitInfo;

	m_CurUnitInfo.HP = 200.f;
	m_CurUnitInfo.Dir = DIRECTION::LEFT;
	SetBossDir(DIRECTION::LEFT);
}

void qBossScript::Tick()
{
	m_PrevUnitInfo = m_CurUnitInfo;

	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vRot = Transform()->GetRelativeRotation();

	if (GetBossDir() == DIRECTION::LEFT)
		vRot.y = 3.141592f;
	else if (GetBossDir() == DIRECTION::RIGHT)
		vRot.y = 0.f;

	Transform()->SetRelativeRotation(vRot);

	// HP ����
	float CurDamage = m_PrevUnitInfo.HP - m_CurUnitInfo.HP;

	static bool flag = false;

	if (m_CurUnitInfo.HP <= 0 && !flag)
	{
		GetOwner()->FSM()->ChangeState(L"BossDeath");

		flag = true;
	}


	// Anim ���� ���� ���� -1: Left , 1: Right
	GetRenderComponent()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, (int)m_CurUnitInfo.Dir);
}

void qBossScript::Hit(float _Damage)
{
	const wstring& CurState = qStateMgr::GetStateName(GetOwner()->FSM()->GetCurState());

	if (CurState == L"qBossDeathState")
		return;

	m_CurUnitInfo.HP -= _Damage;

	GetOwner()->FSM()->ChangeState(L"BossHit");
}



void qBossScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Player")
	{
		wstring CurStateName = qStateMgr::GetStateName(_OtherObject->FSM()->GetCurState());
		if (CurStateName == L"qPlayerDashState")
		{

		}
		else
		{
			_OtherObject->FSM()->ChangeState(L"Bump");
		}

		qPlayerScript* PlayerScript = _OtherObject->GetScript<qPlayerScript>();

		if (PlayerScript == nullptr)
			return;

		// �÷��̾� �Ǳ��
		PlayerScript->Hit(m_BossColiisionDamage);
	}


	if (_OtherObject->GetName() == L"Combo1HitBox" ||
		_OtherObject->GetName() == L"Combo2HitBox" ||
		_OtherObject->GetName() == L"Combo3HitBox")
	{
		Plus10DamageCount();
	}

	if (_OtherObject->GetName() == L"Combo4HitBox")
	{
		Plus20DamageCount();
	}

	if (_OtherObject->GetName() == L"Book")
	{
		Plus30DamageCount();
	}

	if (_OtherObject->GetName() == L"CrashHitBox")
	{
		Plus40DamageCount();
	}

	if (_OtherObject->GetName() == L"RangeHitBox")
	{
		Plus50DamageCount();
	}

}

void qBossScript::Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qBossScript::EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qBossScript::SaveToFile(FILE* _File)
{
}

void qBossScript::LoadFromFile(FILE* _File)
{
}

