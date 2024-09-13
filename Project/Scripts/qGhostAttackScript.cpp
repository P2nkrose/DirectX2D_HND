#include "pch.h"
#include "qGhostAttackScript.h"

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

#include "qPlayerScript.h"
#include "qGhostScript.h"

qGhostAttackScript::qGhostAttackScript()
	: qScript((UINT)SCRIPT_TYPE::GHOSTATTACKSCRIPT)
{

}

qGhostAttackScript::~qGhostAttackScript()
{
}

void qGhostAttackScript::Begin()
{

}

void qGhostAttackScript::Tick()
{

}

void qGhostAttackScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
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

void qGhostAttackScript::Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qGhostAttackScript::EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qGhostAttackScript::SaveToFile(FILE* _File)
{
}

void qGhostAttackScript::LoadFromFile(FILE* _File)
{
}
