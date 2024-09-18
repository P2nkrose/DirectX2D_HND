#include "pch.h"
#include "qClapScript.h"

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>
#include "qCameraMoveScript.h"

qClapScript::qClapScript()
	: qScript((UINT)SCRIPT_TYPE::CLAPSCRIPT)
{
}

qClapScript::~qClapScript()
{
}

void qClapScript::Begin()
{
}

void qClapScript::Tick()
{
}

void qClapScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	qGameObject* Camera = pCurLevel->FindObjectByName(L"MainCamera");
	qGameObject* Boss = pCurLevel->FindObjectByName(L"Boss");

	if (GetOwner() != nullptr)
	{
		if (_OtherObject->GetName() == L"Player")
		{
			qCameraMoveScript* CameraScript = Camera->GetScript<qCameraMoveScript>();
			CameraScript->SetClap(true);

			Boss->FSM()->ChangeState(L"BossIntro");

			GetOwner()->Destroy();
		}
	}

	


}

void qClapScript::Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qClapScript::EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qClapScript::SaveToFile(FILE* _File)
{
}

void qClapScript::LoadFromFile(FILE* _File)
{
}
