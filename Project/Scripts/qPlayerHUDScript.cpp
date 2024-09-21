#include "pch.h"
#include "qPlayerHUDScript.h"

#include <Engine/qSprite.h>

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

#include <Engine/qDevice.h>
#include <Engine/qConstBuffer.h>


qPlayerHUDScript::qPlayerHUDScript()
	: qScript((UINT)SCRIPT_TYPE::PLAYERHUDSCRIPT)
	, m_MaxPlayerHP(413.f)
{

}

qPlayerHUDScript::~qPlayerHUDScript()
{
}

void qPlayerHUDScript::Begin()
{
	

	//GetOwner()->Transform()->SetRelativePos(-100.f, -100.f, 1.f);
	//GetOwner()->Transform()->SetRelativeScale(10.f, 10.f, 1.f);

}

void qPlayerHUDScript::Tick()
{
	qConstBuffer* pCB = qDevice::GetInst()->GetConstBuffer(CB_TYPE::HUD);

	float ratio = 0.7f;
	pCB->SetData(&ratio);

	pCB->Binding();

}

void qPlayerHUDScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qPlayerHUDScript::SaveToFile(FILE* _File)
{
}

void qPlayerHUDScript::LoadFromFile(FILE* _File)
{
}
