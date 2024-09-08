#include "pch.h"
#include "qCollectScript.h"

#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>


qCollectScript::qCollectScript()
	: qScript((UINT)SCRIPT_TYPE::COLLECTSCRIPT)
{
	m_PlayPos = Vec3(-732.f, -87.f, 10.f);
	m_OptionPos = Vec3(-732.f, -151.f, 10.f);
	m_CreditPos = Vec3(-732.f, -214.f, 10.f);
	m_ExitPos = Vec3(-732.f, -278.f, 10.f);
}

qCollectScript::~qCollectScript()
{
}

void qCollectScript::Begin()
{
}

void qCollectScript::Tick()
{
	


	if (GetOwner()->Transform()->GetRelativePos() == m_PlayPos)
	{
		if (KEY_TAP(KEY::DOWN))
		{
			GetOwner()->Transform()->SetRelativePos(m_OptionPos);
		}
	}

	else if (GetOwner()->Transform()->GetRelativePos() == m_OptionPos)
	{
		if (KEY_TAP(KEY::UP))
		{
			GetOwner()->Transform()->SetRelativePos(m_PlayPos);
		}
		else if (KEY_TAP(KEY::DOWN))
		{
			GetOwner()->Transform()->SetRelativePos(m_CreditPos);
		}
	}

	else if (GetOwner()->Transform()->GetRelativePos() == m_CreditPos)
	{
		if (KEY_TAP(KEY::UP))
		{
			GetOwner()->Transform()->SetRelativePos(m_OptionPos);
		}
		else if (KEY_TAP(KEY::DOWN))
		{
			GetOwner()->Transform()->SetRelativePos(m_ExitPos);
		}
	}

	else if (GetOwner()->Transform()->GetRelativePos() == m_ExitPos)
	{
		if (KEY_TAP(KEY::UP))
		{
			GetOwner()->Transform()->SetRelativePos(m_CreditPos);
		}
	}


	if (GetOwner()->Transform()->GetRelativePos() == m_PlayPos)
	{
		if (KEY_TAP(KEY::SPACE))
		{
			qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
			qGameObject* pPostClose = pCurLevel->FindObjectByName(L"PostClose");

			pPostClose->FSM()->ChangeState(L"PostClose");
		}
	}


}

void qCollectScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qCollectScript::SaveToFile(FILE* _File)
{
}

void qCollectScript::LoadFromFile(FILE* _File)
{
}
