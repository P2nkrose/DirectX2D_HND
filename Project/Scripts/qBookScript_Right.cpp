#include "pch.h"
#include "qBookScript_Right.h"

#include <Engine/qGameObject.h>
#include <Engine/qLevelMgr.h>

#include <Engine/qScript.h>
#include "qPlayerScript.h"


qBookScript_Right::qBookScript_Right()
	: qScript(UINT(SCRIPT_TYPE::BOOKSCRIPT_RIGHT))
	, m_BookSpeed(1000.f)
{
}

qBookScript_Right::~qBookScript_Right()
{
}

void qBookScript_Right::Begin()
{
	//GetOwner()->FlipBookComponent()->Play(18, 15, true);
}

void qBookScript_Right::Tick()
{
	//qGameObject* pPlayer = qLevelMgr::GetInst()->FindObjectByName(L"Player");
	//
	//qPlayerScript* pPlayerScript = pPlayer->GetScript<qPlayerScript>();

	Vec3 vPos = Transform()->GetRelativePos();

	vPos.x += DT * m_BookSpeed;

	Transform()->SetRelativePos(vPos);
}

void qBookScript_Right::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
	//if (_OtherObject->GetName() == L"Monster")
	//{
	//	DeleteObject(_OtherObject);
	//}
}

void qBookScript_Right::SaveToFile(FILE* _File)
{
	fwrite(&m_BookSpeed, sizeof(float), 1, _File);
}

void qBookScript_Right::LoadFromFile(FILE* _File)
{
	fread(&m_BookSpeed, sizeof(float), 1, _File);
}
