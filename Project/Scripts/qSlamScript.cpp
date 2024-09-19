#include "pch.h"
#include "qSlamScript.h"

#include <Engine/qState.h>
#include <States/qStateMgr.h>

#include "qPlayerScript.h"

qSlamScript::qSlamScript()
	: qScript((UINT)SCRIPT_TYPE::SLAMSCRIPT)
{
}

qSlamScript::~qSlamScript()
{
}

void qSlamScript::Begin()
{
}

void qSlamScript::Tick()
{
}

void qSlamScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
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

void qSlamScript::SaveToFile(FILE* _File)
{
}

void qSlamScript::LoadFromFile(FILE* _File)
{
}
