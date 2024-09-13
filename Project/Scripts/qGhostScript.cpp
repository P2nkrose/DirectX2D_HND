#include "pch.h"
#include "qGhostScript.h"

#include "qScriptMgr.h"
#include "qPlayerScript.h"
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>
#include <Engine/qRigidBody.h>
#include <Engine/qScript.h>
#include <Engine/qState.h>
#include <States/qStateMgr.h>

qGhostScript::qGhostScript()
	: qScript((UINT)SCRIPT_TYPE::GHOSTSCRIPT)
	, m_DirChanged(false)
	, m_GhostDir(DIRECTION::END)
{
}

qGhostScript::~qGhostScript()
{
}

void qGhostScript::Begin()
{
	m_PrevUnitInfo = m_CurUnitInfo;

	m_CurUnitInfo.HP = 100.f;
	m_CurUnitInfo.Dir = DIRECTION::LEFT;
}

void qGhostScript::Tick()
{
	m_PrevUnitInfo = m_CurUnitInfo;

	Vec3 vRot = Transform()->GetRelativeRotation();

	if (GetGhostDir() == DIRECTION::LEFT)
		vRot.y = 3.141592f;
	else if (GetGhostDir() == DIRECTION::RIGHT)
		vRot.y = 0.f;

	Transform()->SetRelativeRotation(vRot);


	// HP ����
	float CurDamage = m_PrevUnitInfo.HP - m_CurUnitInfo.HP;

	static bool flag = false;

	if (m_CurUnitInfo.HP <= 0 && !flag)
	{
		GetOwner()->FSM()->ChangeState(L"GhostDeath");

		flag = true;
	}

	// Anim ���� ���� ���� -1: Left , 1: Right
	GetRenderComponent()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, (int)m_CurUnitInfo.Dir);
}

void qGhostScript::Hit(float _Damage)
{
	const wstring& CurState = qStateMgr::GetStateName(GetOwner()->FSM()->GetCurState());

	if (CurState == L"qGhostDeathState")
		return;

	m_CurUnitInfo.HP -= _Damage;

	GetOwner()->FSM()->ChangeState(L"GhostHit");
}


void qGhostScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Player")
	{
		_OtherObject->FSM()->ChangeState(L"Bump");
	}

	qPlayerScript* PlayerScript = _OtherObject->GetScript<qPlayerScript>();

	if (PlayerScript == nullptr)
		return;

	// �÷��̾� �Ǳ��
}

void qGhostScript::Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qGhostScript::EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qGhostScript::SaveToFile(FILE* _File)
{
}

void qGhostScript::LoadFromFile(FILE* _File)
{
}

