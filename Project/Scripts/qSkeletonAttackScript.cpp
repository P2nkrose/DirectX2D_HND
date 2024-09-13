#include "pch.h"
#include "qSkeletonAttackScript.h"

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

#include "qPlayerScript.h"

qSkeletonAttackScript::qSkeletonAttackScript()
	: qScript((UINT)SCRIPT_TYPE::SKELETONATTACKSCRIPT)
{
}

qSkeletonAttackScript::~qSkeletonAttackScript()
{
}

void qSkeletonAttackScript::Begin()
{
}

void qSkeletonAttackScript::Tick()
{
}

void qSkeletonAttackScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
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

void qSkeletonAttackScript::Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qSkeletonAttackScript::EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qSkeletonAttackScript::SaveToFile(FILE* _File)
{
}

void qSkeletonAttackScript::LoadFromFile(FILE* _File)
{
}
