#include "pch.h"
#include "qDrownedAttackScript.h"

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

#include "qPlayerScript.h"

qDrownedAttackScript::qDrownedAttackScript()
	: qScript((UINT)SCRIPT_TYPE::DROWNEDATTACKSCRIPT)
{
}

qDrownedAttackScript::~qDrownedAttackScript()
{
}

void qDrownedAttackScript::Begin()
{
}

void qDrownedAttackScript::Tick()
{
}

void qDrownedAttackScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
	if (GetOwner() != nullptr)
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
}

void qDrownedAttackScript::Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qDrownedAttackScript::EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qDrownedAttackScript::SaveToFile(FILE* _File)
{
}

void qDrownedAttackScript::LoadFromFile(FILE* _File)
{
}
