#include "pch.h"
#include "qBleedScript.h"

#include <Engine/qState.h>
#include <States/qStateMgr.h>

#include "qPlayerScript.h"

qBleedScript::qBleedScript()
	: qScript((UINT)SCRIPT_TYPE::BLEEDSCRIPT)
{
}

qBleedScript::~qBleedScript()
{
}

void qBleedScript::Begin()
{
}

void qBleedScript::Tick()
{
}

void qBleedScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
	if (GetOwner() != nullptr)
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
		}

		qPlayerScript* PlayerScript = _OtherObject->GetScript<qPlayerScript>();

		if (PlayerScript == nullptr)
			return;

		// 플레이어 피깎기


	}
}

void qBleedScript::SaveToFile(FILE* _File)
{
}

void qBleedScript::LoadFromFile(FILE* _File)
{
}
