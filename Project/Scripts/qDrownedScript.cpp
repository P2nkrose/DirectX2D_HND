#include "pch.h"
#include "qDrownedScript.h"

#include "qScriptMgr.h"
#include "qPlayerScript.h"
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>
#include <Engine/qRigidBody.h>
#include <Engine/qScript.h>
#include <Engine/qState.h>
#include <States/qStateMgr.h>

qDrownedScript::qDrownedScript()
	: qScript((UINT)SCRIPT_TYPE::DROWNEDSCRIPT)
	, m_DrownedDir(DIRECTION::END)
	, m_DirChanged(false)
{
}

qDrownedScript::~qDrownedScript()
{
}

void qDrownedScript::Begin()
{
	m_PrevUnitInfo = m_CurUnitInfo;

	m_CurUnitInfo.HP = 100.f;
	m_CurUnitInfo.Dir = DIRECTION::LEFT;
	SetDrownedDir(DIRECTION::LEFT);

}

void qDrownedScript::Tick()
{
	m_PrevUnitInfo = m_CurUnitInfo;

	Vec3 vRot = Transform()->GetRelativeRotation();

	if (GetDrownedDir() == DIRECTION::LEFT)
		vRot.y = 3.141592f;
	else if (GetDrownedDir() == DIRECTION::RIGHT)
		vRot.y = 0.f;

	Transform()->SetRelativeRotation(vRot);

	// HP ����
	float CurDamage = m_PrevUnitInfo.HP - m_CurUnitInfo.HP;

	static bool flag = false;

	if (m_CurUnitInfo.HP <= 0 && !flag)
	{
		GetOwner()->FSM()->ChangeState(L"DrownedDeath");

		flag = true;
	}


	// Anim ���� ���� ���� -1: Left , 1: Right
	GetRenderComponent()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, (int)m_CurUnitInfo.Dir);
}

void qDrownedScript::Hit(float _Damage)
{
	const wstring& CurState = qStateMgr::GetStateName(GetOwner()->FSM()->GetCurState());

	if (CurState == L"qDrownedDeathState")
		return;

	m_CurUnitInfo.HP -= _Damage;

	GetOwner()->FSM()->ChangeState(L"DrownedHit");
}



void qDrownedScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
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

void qDrownedScript::Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qDrownedScript::EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qDrownedScript::SaveToFile(FILE* _File)
{
}

void qDrownedScript::LoadFromFile(FILE* _File)
{
}


