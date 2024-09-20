#include "pch.h"
#include "qPlayerHUDScript.h"

#include <Engine/qSprite.h>

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



	Ptr<qMaterial> pPlayerHUDMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"material\\playerHUD.mtrl");
	GetOwner()->MeshRender()->SetMaterial(pPlayerHUDMtrl);

	
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
